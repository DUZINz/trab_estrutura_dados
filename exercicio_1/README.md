# User Management System with AVL Tree

## Overview
This project implements a User Management System using an AVL Tree data structure. The system allows for user registration, removal, searching, and alphabetical listing of users. The AVL Tree ensures that user data is stored in a balanced manner, providing efficient operations.

## Project Structure
```
c-user-management-avl
├── src
│   ├── main.c               # Entry point of the application
│   ├── user.c               # User-related functions
│   ├── avl_tree.c           # AVL tree implementation
│   └── user_management.c     # User management operations
├── include
│   ├── user.h               # User structure and prototypes
│   ├── avl_tree.h           # AVL tree structure and prototypes
│   └── user_management.h     # User management prototypes
├── Makefile                  # Build instructions
└── README.md                 # Project documentation
```

## Setup Instructions
1. Clone the repository or download the project files.
2. Navigate to the project directory.
3. Use the provided Makefile to compile the project:
   ```
   make
   ```

## Usage
- Run the compiled executable to start the User Management System.
- Follow the on-screen menu to register, remove, search for users, or list all users alphabetically.

## Functionality
- **User Registration**: Add a new user to the system.
- **User Removal**: Delete an existing user from the system.
- **User Search**: Find a user by their details.
- **Alphabetical Listing**: Display all users in alphabetical order.

## Dependencies
This project is written in C and requires a standard C compiler to build and run.