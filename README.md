# Autocomplete-Search-Tree
This project implements an autocomplete system using a Binary Search Tree (BST) data structure. It reads a set of terms and associated non-negative weights, then efficiently returns the highest-weighted matches based on a given input prefix — simulating real-world autocomplete behavior used in search engines, apps, and recommendation systems.

## 🚀 Features
Stores terms with weights using a self-built BSTMap class
Performs autocomplete by finding and sorting all matching terms
Supports efficient prefix search with descending weight ranking
Includes full BST traversal: in-order, pre-order, post-order
Rebalancing support for performance optimization
Custom implementation of getAll() to retrieve matching entries

## 🛠 Technologies
C++
Object-Oriented Design
Custom Data Structures (Binary Search Tree)
File I/O
Performance Optimization

📂 Project Structure
graphql
Copy
Edit
├── autocomplete.h      # Autocomplete class definition
├── bstmap.h            # Custom BST map class (STL-like interface)
├── main.cpp            # Example usage / demo CLI
├── cities.txt          # Sample input file with term/weight data
├── README.md

## 📄 Sample Usage
bash
Copy
Edit
$ ./a.out cities.txt Seat
Seattle, Washington, United States         608660
Seaton, South Australia, Australia         9704
Seaton Delaval, United Kingdom             7219
Seaton, United Kingdom                     5240
Seat Pleasant, Maryland, United States     4542

## 🧠 What I Learned
Building a fully functional BST-based map from scratch
Designing extensible classes with modular public/private interfaces
Implementing autocomplete logic using prefix search and weight sorting
Managing file input and parsing large datasets
Optimizing BST performance through rebalancing techniques
