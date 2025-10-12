# Track|It
#### Video Demo:  <[https://youtu.be/MLFJOM169Mk]>

💰 Track|It is an Expense Tracker Web App that is a simple and user-friendly application designed to help individuals manage their personal finances. It allows users to easily record their daily expenses, categorise spending habits, and visualise monthly summaries in real-time.
Built with Python and Flask combined with SQLALCHEMY and SQLite for data management as well as HTML/CSS for the frontend, this webapp emphasises usability, clean design and basic data privacy.

File Structure
The project is organised using a modular structure to promote readability and ongoing code upkeep. The main application logic resides in app.py, which defines routes, models and form handling. The init_db.py file is a separate script created to initialise the database and seed default categories - ensuring that the setup logic is separate from the core app. The HTML templates are stored in the templates/ directory and follow a consistent layout structure with layout.html as the base template, maintaining DRY principles. JavaScript and style logic are in the static/folder, separating presentation from logic, and the requirements.txt file contains all the dependencies for an easy environment setup. I debated using custom categories, but chose predefined ones in order to keep the UX clean and validation simpler. 

✅ Features
1. User Authentication
Track|It provides a secure user authentication system so users' data is protected, and they can log in and log out securely. 
- Register: Create an account with a unique username and password.
- Login: Safely access and exit your account, with session management handled by Flask-Login.
- Logout: Ends the session to keep your data private.
- Password Security: Passwords are safely stored using bcrypt hashing to ensure privacy.

2. Expense Management
Track|It allows users to manage their expenses with ease:
- Amount: Cost of the item/service.
- Name: Description of the expense.
- Date: When the expense occurred.
- Category: Optional category (e.g. Entertainment, Utilities).

Users can:
- Add expenses: Input new expenses with details including amount, description, date and category.
- Edit existing entries: Modify existing entries to keep your records accurate.
- Delete expenses: Remove outdated or incorrect entries.
- View all expenses: Access the list of all your expenses with simple navigation.

3. Expense Categories
Each expense can be assigned a predefined category, enabling users to organise their spending and  gain meaningful insights.

4. Monthly Summaries
The dashboard provides a monthly overview:
- Total Spending: Calculates the sum of expenses for the current month.
- Category Breakdown: Visualises spending patterns across categories with a real-time bar chart.

These summaries are dynamically queried from the database using SQLAlchemy and updated in real time.

5. Dynamic Dashboard
6. Track|It's dashboard is designed to be visually appealing but also minimalistic.
- Expense table: A real-time table of recent expenses, with the options to edit/delete entries.
- Bar Chart Visualisation: A category-wise bar chart.

📊 Bar Chart is rendered using Chart.js and populated dynamically using category_totals passed from the Flask backend.

Tech Stack
⏪ Backend
- Python: The core programming language powering the webapp's logic.
- Flask: Lightweight web framework used to build RESTful routes and manage server-side rendering.
- Flask-login: Manages user sessions, management and authentication.
- SQLAlchemy: Object Relational Mapper (ORM) for database interactions with the database using Python.
- Bcrypt: Ensures password hashing for enhanced security.
- WTForms: Form validation is handled using WTForms to ensure data integrity and improve user input handling.

🎨 Frontend
- HTML/CSS - Structures and styles the user interface for a clean and intuitive experience.
- Chart.js - Provides graphical visualisation of financial data to enhance understanding of spending habits.

🗃️ Database
- SQLite: A lightweight, file-based database system, suitable for small to medium projects.
-  SQLAlchemy: Simplifies database interactions by abstracting SQL queries into Python code.


Installation

1. Clone the Repository
To get Track|It up and running locally, follow these steps:
- git clone https://github.com/AsulaAman/cs50-solutions/tree/master
- cd project

2. Create a Virtual Environment
- python -m venv venv

Activate the environments:
- macOS/Linux: source venv/bin/activate
- Windows: venv/Scripts/activate

3. Install Dependencies
- pip install -r requirements.txt

4. Initialise the DB using Script
Run the included script to create the database and seed default categories:
- python init_db.py

5. Run the WebApp
Launch the Flask development server.
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


Tips for using Track|It
- Always assign categories for better expense tracking.
- Keep your account credentials secure.
- Leverage the edit and delete features to keep your data accurate and up to date.

License
This project is licensed under the MIT License.
