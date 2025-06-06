# 📚 Student Record Management System (COEP)

A command-line based Student Record Management System implemented in C, using a **B+ Tree** as the underlying data structure for efficient storage and querying of student records.

---

## 🚀 Features

- Insert new student records
- Update student details based on MIS
- Search students by MIS or Name *(upcoming)*
- Filter students by:
  - Branch
  - Batch/Graduation Year *(upcoming)*
- Delete student records *(upcoming)*
- Export student records to CSV *(upcoming)*

---

## 📦 Data Structure Used

### 🗂 B+ Tree

This system uses a **B+ Tree**, a balanced tree data structure that maintains sorted data and allows **efficient insertion, deletion, and search operations**.

---

## 🔍 Why B+ Tree?

| Feature                      | Benefit                                                                 |
|-----------------------------|-------------------------------------------------------------------------|
| Balanced Tree               | Guarantees `O(log n)` search, insert, and delete time.                  |
| Ordered Data Storage        | Makes **range queries** (like "students from 2023") efficient.          |
| Leaf Nodes Linked           | Enables fast **in-order traversal** for bulk record listing.            |
| Disk-optimized              | Widely used in **databases and filesystems** for scalable performance.  |

---

## 🧠 Why It's Best for Student Record Management

Managing thousands of student records demands a structure that is:

- **Fast to search** by MIS or name
- **Efficient to update** without re-indexing
- **Capable of range queries** (e.g., all students from "CSE", or from batch "2024")
- **Scalable**, as student count grows every year

The **B+ Tree** satisfies all these requirements. Unlike arrays or linked lists, it doesn’t slow down as data grows. And unlike hash tables, it maintains **sorted order**, making it ideal for both **precise lookups and range queries**.

