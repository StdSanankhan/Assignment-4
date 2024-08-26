#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Item {
protected:
    
    string title;
    bool availability;

public:
    string itemID;
    Item(const string& id, const string& t, bool avail = true)
        : itemID(id), title(t), availability(avail) {}

    virtual ~Item() {}

    virtual void getItemDetails() const = 0;
    virtual bool checkAvailability() const = 0;
    virtual void checkOut() = 0;
    virtual void checkIn() = 0;
};

class Book : public Item {
private:
    string author;
    string ISBN;

public:
    Book(const string& id, const string& t, const string& a, const string& isbn)
        : Item(id, t), author(a), ISBN(isbn) {}

    void getItemDetails() const override {
        cout << "Book ID: " << itemID << "\nTitle: " << title
            << "\nAuthor: " << author << "\nISBN: " << ISBN
            << "\nAvailability: " << (availability ? "Available" : "Not Available") << endl;
    }

    bool checkAvailability() const override {
        return availability;
    }

    void checkOut() override {
        if (availability) {
            availability = false;
            cout << "Book checked out successfully.\n";
        }
        else {
            cout << "Book is not available for checkout.\n";
        }
    }

    void checkIn() override {
        availability = true;
        cout << "Book checked in successfully.\n";
    }
};

class Journal : public Item {
private:
    string publisher;
    int issueNumber;

public:
    Journal(const string& id, const string& t, const string& p, int issue)
        : Item(id, t), publisher(p), issueNumber(issue) {}

    void getItemDetails() const override {
        cout << "Journal ID: " << itemID << "\nTitle: " << title
            << "\nPublisher: " << publisher << "\nIssue Number: " << issueNumber
            << "\nAvailability: " << (availability ? "Available" : "Not Available") << endl;
    }

    bool checkAvailability() const override {
        return availability;
    }

    void checkOut() override {
        if (availability) {
            availability = false;
            cout << "Journal checked out successfully.\n";
        }
        else {
            cout << "Journal is not available for checkout.\n";
        }
    }

    void checkIn() override {
        availability = true;
        cout << "Journal checked in successfully.\n";
    }
};

class Member {
private:
    string memberID;
    string name;
    string contactInfo;
    int loanLimit;
    vector<string> loanHistory;

public:
    Member(const string& id, const string& n, const string& contact, int limit)
        : memberID(id), name(n), contactInfo(contact), loanLimit(limit) {}

    void borrowItem(Item& item) {
        if (loanHistory.size() < loanLimit) {
            if (item.checkAvailability()) {
                item.checkOut();
                loanHistory.push_back(item.itemID);
                cout << name << " borrowed the item: " << item.itemID << "\n";
            }
            else {
                cout << "Item is not available for borrowing.\n";
            }
        }
        else {
            cout << "Loan limit reached.\n";
        }
    }

    void returnItem(Item& item) {
        item.checkIn();
        for (size_t i = 0; i < loanHistory.size(); ++i) {
            if (loanHistory[i] == item.itemID) {
                loanHistory.erase(loanHistory.begin() + i);
                break;
            }
        }
        cout << name << " returned the item: " << item.itemID << "\n";
    }

    void getLoanHistory() const {
        cout << "Loan History of " << name << ":\n";
        for (const auto& id : loanHistory) {
            cout << id << "\n";
        }
    }
};

class Loan {
private:
    string loanID;
    Item& item;
    Member& member;
    int dueDate; // Use days as an integer to represent the due date
    int actualReturnDate;

public:
    Loan(const string& id, Item& i, Member& m, int due)
        : loanID(id), item(i), member(m), dueDate(due), actualReturnDate(0) {}

    void returnItem(int returnDate) {
        actualReturnDate = returnDate;
        item.checkIn();
    }

    double calculateFine() const {
        if (actualReturnDate > dueDate) {
            double finePerDay = 1.0; // example fine rate
            int overdueDays = actualReturnDate - dueDate;
            return overdueDays * finePerDay;
        }
        return 0.0;
    }
};

// Example Usage
int main() {
    Book book1("B001", "C++ Programming", "Bjarne Stroustrup", "123-456-789");
    Journal journal1("J001", "IEEE Transactions on Computers", "IEEE", 42);

    Member member1("M001", "Alice", "alice@example.com", 3);

    book1.getItemDetails();
    journal1.getItemDetails();

    member1.borrowItem(book1);
    member1.getLoanHistory();

    member1.returnItem(book1);
    member1.getLoanHistory();

    return 0;
}
