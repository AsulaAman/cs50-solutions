import os
from collections import defaultdict
from flask import Flask, render_template, redirect, url_for, flash, request
from flask_sqlalchemy import SQLAlchemy
from flask_login import UserMixin, LoginManager, login_user, login_required, logout_user, current_user
from flask_wtf import FlaskForm
from datetime import datetime, timezone
from wtforms import StringField, PasswordField, SubmitField
from wtforms.validators import DataRequired, Length, ValidationError
from flask_bcrypt import Bcrypt

app = Flask(__name__)
bcrypt = Bcrypt(app)

basedir = os.path.abspath(os.path.dirname(__file__))
app.config['SQLALCHEMY_DATABASE_URI'] = f"sqlite:///{os.path.join(basedir, 'database.db')}"
app.config['SQLALCHEMY_TRACK_MODIFICATIONS'] = False
app.config['SECRET_KEY'] = 'your_secret_key'

login_manager = LoginManager()
login_manager.init_app(app)
login_manager.login_view = 'login'

@login_manager.user_loader
def load_user(user_id):
    return User.query.get(int(user_id))


db = SQLAlchemy(app)

class User(db.Model, UserMixin):
    id = db.Column(db.Integer, primary_key=True)
    username = db.Column(db.String(20), nullable=False, unique=True)
    password = db.Column(db.String(80), nullable=False)

class Category(db.Model):
    id = db.Column(db.Integer, primary_key=True)
    name = db.Column(db.String(50), nullable=False, unique=True)
    expenses = db.relationship('Expense', backref='category_obj', lazy=True, overlaps="category")

class Expense(db.Model):
    id = db.Column(db.Integer, primary_key=True)
    amount = db.Column(db.Float, nullable=False)
    name = db.Column(db.String(100), nullable=False)
    date = db.Column(db.DateTime, default=lambda: datetime.now(timezone.utc))

    category_id = db.Column(db.Integer, db.ForeignKey('category.id'), nullable=True)
    category = db.relationship('Category', overlaps="category_obj")
    user_id = db.Column(db.Integer, db.ForeignKey('user.id'), nullable=False)

    def __repr__(self):
        return f"<Expense {self.name} - {self.amount}>"

class RegistrationForm(FlaskForm):
    username = StringField(validators=[DataRequired(),
        Length(min=5, max=20)], render_kw={"placeholder": "Username"})

    password = PasswordField(validators=[DataRequired(),
        Length(min=5, max=20)], render_kw={"placeholder": "Password"})

    submit = SubmitField("Register")

    def validate_username(self, username):
        existing_user_username = User.query.filter_by(username=username.data).first()
        if existing_user_username:
            raise ValidationError("That username already exists. Please choose a different one.")

class LoginForm(FlaskForm):
   username = StringField(validators=[DataRequired(),
        Length(min=5, max=20)], render_kw={"placeholder": "Username"})

   password = PasswordField(validators=[DataRequired(),
        Length(min=5, max=20)], render_kw={"placeholder": "Password"})

   submit = SubmitField("Login")

@app.route('/')
def home():
    return render_template('index.html')

@app.route('/login', methods=['GET', 'POST'])
def login():
    form = LoginForm()
    if form.validate_on_submit():
        user = User.query.filter_by(username=form.username.data).first()
        if user:
            if bcrypt.check_password_hash(user.password, form.password.data):
                login_user(user)
                print("Logged in successfully.")
                return redirect(url_for('dashboard'))
            else:
                flash('Login Unsuccessful. Please check username and password', 'danger')
    return render_template('login.html', form=form)

@app.route('/dashboard', methods=['GET', 'POST'])
@login_required
def dashboard():
    start = datetime(datetime.now().year, datetime.now().month, 1)
    expenses = Expense.query.filter(
        Expense.user_id == current_user.id,
        Expense.date >= start).all()

    total = sum(expense.amount for expense in expenses)

    category_totals = defaultdict(float)
    for expense in expenses:
        if expense.category_id:
            category = Category.query.get(expense.category_id)
            category_name = category.name if category else "Uncategorized"
            category_totals[category_name] += expense.amount
        else:
            category_totals["Uncategorized"] += expense.amount

    print(f"Total expenses for the month: {total}")
    return render_template('dashboard.html', expenses=expenses, total=total, category_totals=category_totals)

@app.route('/logout', methods=['GET', 'POST'])
@login_required
def logout():
    logout_user()
    return redirect(url_for('login'))

@app.route('/register', methods=['GET', 'POST'])
def register():
    form = RegistrationForm()

    if form.validate_on_submit():
        hashed_password = bcrypt.generate_password_hash(form.password.data).decode('utf-8')
        new_user = User(username=form.username.data, password=hashed_password)
        db.session.add(new_user)
        db.session.commit()
        flash('Registration Successful')
        return redirect(url_for('login'))

    return render_template('register.html', form=form)

@app.route('/add_expense', methods=['GET', 'POST'])
@login_required
def add_expense():
    categories = Category.query.all()

    if request.method == 'POST':
        name = request.form['name']
        amount = float(request.form['amount'])
        category_raw = request.form.get('category')

        if not category_raw:
            flash('Please select a category', 'danger')
            return redirect(url_for('add_expense'))
        category_id = int(category_raw)

        expense = Expense(
            name=name,
            amount=amount,
            category_id=int(category_id),
            user_id=current_user.id
        )
        db.session.add(expense)
        db.session.commit()
        flash('Expense added successfully!', 'success')
        return redirect(url_for('dashboard'))
    return render_template('add_expense.html', categories=categories)

@app.route('/edit/<int:expense_id>', methods=['GET', 'POST'])
@login_required
def edit(expense_id):
    expense = Expense.query.get_or_404(expense_id)
    if expense.user_id != current_user.id:
        return redirect(url_for('dashboard'))
    categories = Category.query.all()
    if request.method == 'POST':
        expense.name = request.form['name']
        expense.amount = float(request.form['amount'])
        expense.category_id = int(request.form.get('category'))
        db.session.commit()
        flash("expense updated successfully!", 'success')
        return redirect(url_for('dashboard'))
    return render_template('edit_expense.html', expense=expense, categories=categories)

@app.route('/delete/<int:expense_id>', methods=['POST'])
@login_required
def delete(expense_id):
    expense = Expense.query.get_or_404(expense_id)
    if expense.user_id != current_user.id:
        return redirect(url_for('dashboard'))

    if request.method == 'POST':
        db.session.delete(expense)
        db.session.commit()
        flash("expense deleted successfully!", 'success')
        return redirect(url_for('dashboard'))
    return render_template('dashboard.html')



if __name__ == '__main__':
    app.run(debug=True)
