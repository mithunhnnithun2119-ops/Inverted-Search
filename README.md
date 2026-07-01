<div align="center">

<img width="100%" src="https://capsule-render.vercel.app/api?type=waving&color=0:0d1117,30:0a3d62,60:1a1a2e,100:16213e&height=260&section=header&text=Inverted%20Search%20Engine&fontSize=52&fontColor=00d4ff&fontAlignY=45&desc=Word%20Indexing%20%26%20Search%20Engine%20in%20Pure%20C&descSize=20&descColor=a0cfee&descAlignY=65&animation=fadeIn&stroke=00d4ff&strokeWidth=1"/>

<img src="https://readme-typing-svg.demolab.com?font=Fira+Code&weight=700&size=19&duration=2500&pause=900&color=00D4FF&center=true&vCenter=true&width=680&lines=🔍+Index+Any+Word+Across+Multiple+Files;⚡+O(1)+Average+Lookup+via+Hash+Table;🔗+Linked+List+Stores+File+%26+Frequency+Data;💾+Save+%26+Load+Database+from+Disk;🧠+Built+in+Pure+C+—+No+External+Libraries" alt="Typing SVG" />

<br/>

![Language](https://img.shields.io/badge/Language-C-00599C?style=for-the-badge&logo=c&logoColor=white)
![DSA](https://img.shields.io/badge/DSA-Hash%20Table%20%26%20Linked%20List-00599C?style=for-the-badge&logo=c&logoColor=white)
![Build](https://img.shields.io/badge/Build-GCC-orange?style=for-the-badge&logo=gnu&logoColor=white)
![Status](https://img.shields.io/badge/Status-Complete-brightgreen?style=for-the-badge)

</div>

---

## 📌 Overview

**Inverted Search Engine** is a command-line word-indexing system built entirely in **C** that reads multiple `.txt` files, indexes every word using a **Hash Table**, and allows instant keyword lookup — returning which files contain the word and how many times it appears.

The core idea mirrors how real-world search engines like Google build their indexes — words mapped to a list of documents that contain them. This implementation does it from scratch using **hashing**, **linked lists**, **dynamic memory**, and **file I/O** — no external libraries, no shortcuts.

---

## ✨ Features

| Feature | Description |
|---------|-------------|
| 📂 **Multi-file Indexing** | Reads and indexes words from multiple `.txt` files at once |
| ⚡ **O(1) Average Lookup** | Hash table gives near-instant word search results |
| 🔗 **Linked List per Word** | Each hash entry holds a list of file names + occurrence count |
| 💾 **Save Database** | Persist the entire index to disk for reuse |
| 📂 **Load Database** | Reload a previously saved index without re-reading source files |
| 🖥️ **Display Index** | Print all indexed words and their file occurrences |
| 🔍 **Keyword Search** | Search any word and get back file name + frequency |
| ✅ **Input Validation** | Handles duplicate files, empty files, invalid extensions gracefully |

---

## 📁 Project Structure

```
📁 inverted-search/
│
├── 📄 main.c              → Entry point, menu loop, operation dispatch
├── 📄 index.c             → Hash table creation, word insertion, search
├── 📄 index.h             → Struct definitions and function declarations
├── 📄 linked_list.c       → Per-word linked list: add file, update count
├── 📄 linked_list.h       → Linked list declarations
├── 📄 file_handler.c      → File reading, save/load database to disk
├── 📄 file_handler.h      → File operation declarations
├── 📄 utils.c             → String helpers, extension validator, lowercase
├── 📄 utils.h             → Utility declarations
├── 📄 Makefile            → Build automation
└── 📄 README.md           → You are here
```

---

## 🚀 Getting Started

### Prerequisites

```bash
# Verify GCC is installed
gcc --version

# Install on Ubuntu / Debian
sudo apt install gcc build-essential

# Install on Fedora / RHEL
sudo dnf install gcc make
```

### Build

```bash
# Clone the repository
git clone https://github.com/mithunhnnithun2119-ops/inverted-search.git
cd inverted-search

# Build with Makefile
make

# Or compile manually
gcc main.c index.c linked_list.c file_handler.c utils.c -o inverted_search
```

---

## 🖥️ Usage

### Syntax

```bash
./inverted_search
```

The program launches an interactive menu:

```
╔══════════════════════════════════════════╗
║     🔍  INVERTED SEARCH ENGINE  v1.0    ║
║           by Mithun H N                 ║
╠══════════════════════════════════════════╣
║                                          ║
║   [1]  📂  Create Database               ║
║   [2]  🔍  Search a Word                 ║
║   [3]  🖥️  Display Index                 ║
║   [4]  💾  Save Database to File         ║
║   [5]  📂  Load Database from File       ║
║   [0]  ❌  Exit                          ║
║                                          ║
╚══════════════════════════════════════════╝

Enter your choice: _
```

---

## 🎬 Demo

### Creating the Database

```bash
Enter number of files: 3
Enter file 1: file1.txt
Enter file 2: file2.txt
Enter file 3: file3.txt

✅ Database created successfully! 1,284 unique words indexed.
```

### Searching a Word

```bash
Enter word to search: embedded

🔍 Search Result for: "embedded"
┌──────────────────┬───────────┐
│  File Name       │  Count    │
├──────────────────┼───────────┤
│  file1.txt       │  5        │
│  file3.txt       │  2        │
└──────────────────┴───────────┘
Total occurrences : 7
```

### Word Not Found

```bash
Enter word to search: quantum

❌ Word "quantum" not found in the database.
```

### Invalid File Handling

```bash
Enter file 1: notes.pdf

❌ Error: "notes.pdf" — Only .txt files are supported.
```

---

## 🧠 Technical Deep Dive

### What Is an Inverted Index?

A **forward index** maps: `document → list of words`
An **inverted index** maps: `word → list of documents`

```
Forward  :  file1.txt  →  ["embedded", "systems", "C", "hardware"]
Inverted :  "embedded" →  [file1.txt(5), file3.txt(2)]
            "systems"  →  [file1.txt(3), file2.txt(1)]
            "C"        →  [file1.txt(8), file2.txt(4), file3.txt(6)]
```

This is exactly how search engines index the web — and this project builds it from scratch.

### Hash Table Design

```c
#define TABLE_SIZE 1024

/* Each bucket holds a linked list of WordEntry nodes */
typedef struct WordEntry {
    char         word[64];     /* Indexed word (lowercased)    */
    FileNode    *file_list;    /* Linked list of file records  */
    struct WordEntry *next;    /* Chaining for hash collisions */
} WordEntry;

/* The hash table — array of WordEntry pointers */
WordEntry *hash_table[TABLE_SIZE];
```

### Hash Function

```c
/* djb2 hash — fast and low collision for word strings */
unsigned int hash(const char *word) {
    unsigned int hash = 5381;
    int c;
    while ((c = *word++))
        hash = ((hash << 5) + hash) + c;   /* hash * 33 + c */
    return hash % TABLE_SIZE;
}
```

### Per-Word File Linked List

```c
/* One node per file that contains the word */
typedef struct FileNode {
    char          filename[128];   /* Source file name      */
    int           count;           /* Occurrence count      */
    struct FileNode *next;         /* Next file in the list */
} FileNode;
```

### Word Insertion Logic

```c
/*
 * For each word in a file:
 * 1. Hash the word → get bucket index
 * 2. If word exists in bucket → update its FileNode count
 * 3. If word is new → create WordEntry, add FileNode, insert to bucket
 */
void insert_word(const char *word, const char *filename) {
    unsigned int idx   = hash(word);
    WordEntry   *entry = find_word(hash_table[idx], word);

    if (entry) {
        update_file_count(entry->file_list, filename);
    } else {
        WordEntry *new_entry   = create_word_entry(word);
        new_entry->file_list   = create_file_node(filename);
        new_entry->next        = hash_table[idx];
        hash_table[idx]        = new_entry;
    }
}
```

### Search Logic

```c
/* Search: hash the query word, walk the bucket chain */
WordEntry* search_word(const char *word) {
    unsigned int idx   = hash(word);
    WordEntry   *entry = hash_table[idx];

    while (entry) {
        if (strcasecmp(entry->word, word) == 0)
            return entry;   /* Found */
        entry = entry->next;
    }
    return NULL;            /* Not found */
}
```

---

## ⚙️ Key Concepts Applied

| Concept | Application |
|---------|-------------|
| `Hash Table` | Core index structure — O(1) average word lookup |
| `Chaining (Collision Handling)` | Linked list per bucket for collision resolution |
| `Singly Linked List` | Per-word file list storing filename + count |
| `Dynamic Memory Allocation` | `malloc()` per word entry and file node |
| `File I/O` | Reading `.txt` files word-by-word; save/load index to disk |
| `String Functions` | `strcasecmp()`, `strtok()`, `strcpy()` for word processing |
| `Modular Programming` | Separate modules: index, linked_list, file_handler, utils |
| `Input Validation` | Extension check, duplicate file detection, empty file handling |

---

## 🧪 Challenges & Solutions

```
❌ Challenge 1: Efficiently storing word-to-file mappings
✅ Solution   : Used a hash table with chaining — each bucket holds a
                linked list of WordEntry nodes, giving O(1) average
                insert and lookup regardless of word count.

❌ Challenge 2: Hash collisions corrupting word entries
✅ Solution   : Implemented chaining — when two words hash to the same
                bucket, they are linked together and searched linearly
                within that bucket using strcasecmp().

❌ Challenge 3: Segfaults when reading files with special characters
✅ Solution   : Used strtok() with a broad delimiter set to safely
                tokenize words, skipping punctuation and whitespace
                without accessing out-of-bound memory.

❌ Challenge 4: Duplicate file entries inflating word counts
✅ Solution   : Added a file validation step before indexing — each
                filename is checked against an already-processed list
                before its words are added to the index.

❌ Challenge 5: Saving and reloading the index without data loss
✅ Solution   : Serialized the hash table to a binary file using
                fwrite() — storing word, filename, and count per
                record — and reloaded it with fread() on startup.
```

---

## 📈 Future Enhancements

- [ ] 🔤 Stemming support — index "running", "runs", "ran" as one word
- [ ] 📊 Rank results by frequency (most relevant file first)
- [ ] 🌐 Support for `.csv`, `.log`, and `.json` file formats
- [ ] ⚡ Resize hash table dynamically when load factor exceeds threshold
- [ ] 🖥️ Interactive REPL mode with persistent session
- [ ] 📤 Export search results to a `.txt` report file

---

## 🎓 Learning Outcomes

Building this project gave me hands-on experience in:

- **Hash table design** — choosing table size, hash function, and collision strategy
- **Linked list management** — per-word file chains with dynamic allocation
- **File I/O in C** — reading word-by-word, serializing and deserializing data
- **String processing** — tokenizing, lowercasing, and comparing words safely
- **Modular C architecture** — clean separation across 5 source files
- **Real-world data structure application** — implementing what powers actual search engines

---

## 👤 Author

<div align="center">

| Field | Details |
|-------|---------|
| **Name** | Mithun H N |
| **Degree** | B.E. ECE — Visvesvaraya Technological University (CGPA: 8.13) |
| **Training** | Advanced Embedded Systems — Emertxe, Bangalore |
| **Certification** | Skill India / NSDC — ELE/Q1501 (Embedded Engineer) |
| **LinkedIn** | [linkedin.com/in/mithun-hn](https://www.linkedin.com/in/mithun-hn) |
| **GitHub** | [github.com/mithunhnnithun2119-ops](https://github.com/mithunhnnithun2119-ops) |
| **Email** | mithunhnmithun2119@gmail.com |

</div>

---

<div align="center">

<img width="100%" src="https://capsule-render.vercel.app/api?type=waving&color=0:16213e,50:1a1a2e,100:0d1117&height=120&section=footer&animation=fadeIn"/>

*"Index everything. Find anything. In O(1)."* ⚡

![Visitor Count](https://komarev.com/ghpvc/?username=mithunhnnithun2119-ops&color=00d4ff&style=for-the-badge&label=PROFILE+VIEWS)

⭐ **Star this repo if it helped you!** ⭐

</div>
