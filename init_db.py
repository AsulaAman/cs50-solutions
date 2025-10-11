from app import app, db, Category

def seed_categories():
    default_categories = ['Groceries', 'Transportation', 'Utilities', 'Entertainment', 'Health & Wellness']
    for name in default_categories:
        if not Category.query.filter_by(name=name).first():
            db.session.add(Category(name=name))
    db.session.commit()
    print("Categories seeded successfully.")

if __name__ == '__main__':
    with app.app_context():
        db.create_all()
        seed_categories()
