# BUDGET BUDDY
## Video Demo:
#### https://youtu.be/PLzdL7y8OXU
<br/>

## Source Code:
#### https://github.com/taran01/CS50x/tree/main/cs50x%20project
<br/>

## Description:

<br>

### **Project Overview:**
Final Project for Harvard's CS50's Introduction to Computer Science.
A web-app made using python, flask and some javascript. Instructinos about the web-app are shown in video linked above.
<br>
I have css files in static, all html in templates, have a helpers.py file which contains herlper functions, money.db is my database and app.py where all routes are explained.

<br>

### **helpers.py:**
In this file there are three functions: apology, login_required and usd.
1. apology returns a meme picture with error text given by dev.
2. login_required is a decorator which makes sure user is logged in.
3. usd just formats numbers in jinja. It adds $ sign and formats the numbers to 2 decimals.

<br>

### **money.db:**
In money.db I've three tables: users, income, expense.
1. Users table contains three columns: id - user's unique id, username - which have name of users and hash - password hash.
2. Income table contains six columns: id - uniue id of enitry, username - name of user, timestamp - date/time of entry, amount - amount of entry, category - type of entry, and note - optional note.
3. Expense table is same as income table.

<br>

### **app.py:**
In app.py all the routes and other functions are written.First I have two const lists which are used for validation further below.Then I use Flask module to make app object. Then there's some configurations for session and cookies. I've db as my sqlite3 database. I've created a function format_timestamp which I needed to convert time.

My first ***route"/"(index)*** gets data from **money.db** for both income and expense (also total sum of income and expense) and renders that data as a table in **index.html**. If user is not logged in, this route redirects user to **login.html**.

***route("/login")*** works both with `get` and `post`. This functions first clears any previous session. When get is used, it just renders **login.html**. When post is used it validates if the required input is given and then checks for the user in database. If the given username and password is in database it logs in the user, sets sessions's values to the user's credentials, and redirects to **"/"**.

***route("/logout")*** clears the session and redirects to **"/"**.

***route("/register")*** uses both `get` and `post`. When using get, renders **register.html**.
When using post it gets username, password and confirmation password from user's submitted form and checks for validation. Then it checks if the given username is not in database. If username is available to take it insers the user details in database. and serts session credentials to user's details. It then redirects to **"/"**.

***route("/ch_password")*** renders **password.html** when using get. When using post it gets the values from submitted form and validates them. Then checks if given password matches with password in database. If matches, it changes the **hash** in **users** table in database.


***route("add_income")*** renders **income.html** when using get. When using post it gets the values from user and validates them and inserts them in database's income table.

***route("add_expense")*** renders **expense.html** when using get. When using post it gets the values from user and validates them and inserts them in database's expense table.

***route("/daily")*** renders **daily.html** which shows two tables for income and expense of only current day.

***route("/search")*** renders **search.html**

***route("/query")*** gets both from and to dates from **search.html**'s form and returns tables for both income and expense. The data from database is only with the given **from** and **to** dates.

***route("/delete")*** rendres **delete.html** when using get. When using post, the data given by user is in json. So first it converts that data and gets **from** and **to** dates and searches for entries between those dates. Then renders that data with delete button.


***route("/delete_entry")*** gets id and type from user. If type is "income" it deletes that entry from database's income table and if type is "expense" it delets that entry from database's expense table.

<br>

### **Templates:**
daily, index, delete_entry and query all four html files renders two tables for both income and expense.

delete, search, expense, income, login, password and register all renders froms to get data from user.

apology renders meme with error text.

layout renders basic navbar and sidebar of site.

