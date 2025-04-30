# Autocomplete-Search-Tree
This project implements an autocomplete system using a Binary Search Tree (BST) data structure. It reads a set of terms and associated non-negative weights, then efficiently returns the highest-weighted matches based on a given input prefix — simulating real-world autocomplete behavior used in search engines, apps, and recommendation systems.

## 🚀 Features
<ul>
  <li>Stores terms with weights using a self-built <code>BSTMap</code> class</li>
  <li>Performs autocomplete by finding and sorting all matching terms</li>
  <li>Supports efficient prefix search with descending weight ranking</li>
  <li>Includes full BST traversal: in-order, pre-order, post-order</li>
  <li>Rebalancing support for performance optimization</li>
  <li>Custom implementation of <code>getAll()</code> to retrieve matching entries</li>
</ul>

## 🛠 Technologies
<ul>
  <li>C++</li>
  <li>Object-Oriented Design</li>
  <li>Custom Data Structures (Binary Search Tree)</li>
  <li>File I/O</li>
  <li>Performance Optimization</li>
</ul>

## 📂 Project Structure
<pre><code>
├── autocomplete.h      # Autocomplete class definition
├── bstmap.h            # Custom BST map class (STL-like interface)
├── main.cpp            # Example usage / demo CLI
├── cities.txt          # Sample input file with term/weight data
├── README.md
</code></pre>

## 📄 Sample Usage
<pre><code>
$ ./a.out cities.txt Seat
Seattle, Washington, United States         608660
Seaton, South Australia, Australia         9704
Seaton Delaval, United Kingdom             7219
Seaton, United Kingdom                     5240
Seat Pleasant, Maryland, United States     4542
</code></pre>

## 🧠 What I Learned
<ul>
  <li>Building a fully functional <strong>BST-based map</strong> from scratch</li>
  <li>Designing extensible classes with <strong>modular public/private interfaces</strong></li>
  <li>Implementing <strong>autocomplete logic</strong> using prefix search and weight sorting</li>
  <li>Managing <strong>file input and parsing</strong> large datasets</li>
  <li>Optimizing BST performance through <strong>rebalancing</strong> techniques</li>
</ul>
