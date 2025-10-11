# Track|It
#### Video Demo:  <[https://youtu.be/MLFJOM169Mk]>

💰 Track|It is an Expense Tracker Web App that is a simple and user-friendly application designed to help individuals manage their personal finances. It allows users to track expenses, categorise spending and visualise monthly summaries in real time.
Built with Python, Flask, SQLALCHEMY and HTML/CSS, this webapp emphasises usability, clean design and basic data privacy.

✅ Features
1. User Authentication
Users can create an account, log in and log out securely
- Register: Create an account with a unique username and password.
- Login: Safely access your account.
- Logout: Ends the session to keep your data private.

2. Expense Management
Each expense includes:
- Amount: Cost of the item/service.
- Name: Description of the expense.
- Date: When the expense occurred.
- Category: Optional category (e.g. Entertainment, Utilities).

Users can:
- Add new expenses
- Edit existing entries
- Delete expenses
- View all expenses

🗒️ Form validation is handled using WTForms to ensure data integrity.

3. Expense Categories
Each expense can be assigned a predefined category which can help users organise their spending, providing clearer insights.

4. Monthly Summaries
The dashbpard provides a monthly overview:
- Total Spending: Sum of expenses for the current month.
- Category Breakdown: Grouped view of spending by category.

These summaries are dynamically queried from the database using SQLAlchemy and updated in real time.

5. Dynamic Dashboard
- A real-time table of recent expenses, with the options to edit/delete entries.
- A bar chart visualising category-wise breakdown.

📊 Bar Chart is rendered using Chart.js and populated dynamically using category_totals passed from the Flask backend.

Tech Stack
⏪ Backend
- Python: Core programming language.
- Flask-login: Session and user management.
- SQLAlchemy: Object Relational Mapper (ORM) for database interactions using Python.
- Bcrypt: Password hashing.
- WTForms: Form validation.

🎨 Frontend
- HTML/CSS - Layout and styling.
- Chart.js - Bar chart rendering for dashboard.

🗃️ Database
- SQLite: Lightweight database stored in a single file.
-  SQLAlchemy: Provides high-level Python interface for querying and managing the database.


Installation

1. Clone the Repository
- git clone https://github.com/AsulaAman/cs50-solutions/tree/master
- cd project

2. Create a Virtual Environment
- python -m venv venv

Activate the environments:
- macOS/Linus: source venv/bin/activate
- Windows: venv/Scripts/activate

3. Install Dependencies
- pip install -r requirements.txt

4. Initialise the DB using Script
Run the included script to create the database and seed default categories:
- python init_db.py

5. Run the WebApp
- flask run

Usage
Route                   Description
/                       Home page
/register               Register new user
/login                  Log in to your account
/dashboard              View your dashboard
/add_expense            Add a new expense
/edit/<expense_id>      Edit an existing expense
/delete/<expense_id>    Delete an expense
/logout                 Logout of your session


License
This project is licensed under the MIT License.
