#include "Tree.h"
#include <iostream>
#include <queue>

Tree::Tree()
    : root(0) {}

Tree::~Tree(){
    destruct(root);
    root = 0;
}

void Tree::destruct(Node* val){
    if (!val){
        return;
    }
    destruct(val->left);
    destruct(val->middle);
    destruct(val->right);

    delete val;
}

void Tree::insert(const string & word){
    if (!root){
        root = new Node();
        root->small = word;
    }else{
        insertHelper(root, root, word);
    }
}

void Tree::insertHelper(Node* val, Node* prev, const string & word){
    if (!val->left && !val->middle && !val->right){
        if (val->small != "" && val->large != ""){
            split(val, prev, 0, 0, word);
        }else if (word > val->small){
            val->large = word;
        }else{
            val->large = val->small;
            val->small = word;
        }
    }else if (val->large == ""){
        if (word < val->small) {
            insertHelper(val->left, val, word);
        }else {
            insertHelper(val->middle, val, word);
        }
    }else{
        if (word < val->small){
            insertHelper(val->left, val, word);
        }else if (word <= val->large){
            insertHelper(val->middle, val, word);
        }else{
            insertHelper(val->right, val, word);
        }
    }
}

void Tree::split(Node* val, Node* parent, Node* lChild, Node* rChild, const string & word){
    if (lChild && rChild){
        if (val->middle == lChild){ // assigns children to the correct spot if the previous split is on middle child
            Node* smallsLeft = val->left;
            Node* largesRight = val->right;
            Node* large = new Node;
            string middle = "";
            setVals(val, large, middle, word);
            val->left = smallsLeft;
            val->right = 0;
            val->middle = lChild;
            large->parent = val->parent;
            large->left = rChild;
            large->middle = largesRight;
            // large->right = 0;
            if (val == root){ // if the value is the root then the middle value becomes the new root
                root = new Node(middle);
                root->left = val;
                root->middle = large;
                val->parent = root;
                large->parent = root;
                return;
            }
            if (parent->large == ""){ // simple adding pushed middle value into a 2node
                if (middle < parent->small){
                    parent->large = parent->small;
                    parent->small = middle;
                }else{
                    parent->large = middle;
                }
                parent->right = parent->middle;
                parent->middle = large;
            }else{
                split(parent, parent->parent, val, large, middle);
            }
        }else if (val->left == lChild){ // recursive split based on previous split being on the left child
            Node* largesLeft = val->middle;
            Node* largesRight = val->right;
            Node* large = new Node;
            string middle = "";
            setVals(val, large, middle, word);
            val->left = lChild;
            val->middle = rChild;
            // val->right = 0;
            large->parent = val->parent;
            large->left = largesLeft;
            large->middle = largesRight;
            // large->right = 0;
            if (val == root){
                root = new Node(middle);
                root->left = val;
                root->middle = large;
                val->parent = root;
                large->parent = root;
                return;
            }
            if (parent->large == ""){
                if (middle < parent->small){
                    parent->large = parent->small;
                    parent->small = middle;
                }else{
                    parent->large = middle;
                }
                parent->left = large;
            }else{
                split(parent, parent->parent, val, large, middle);
            }
        }else{ // else the node that was split previously was the right child
            Node* smallsLeft = val->left;
            Node* smallsRight = val->middle;
            Node* large = new Node;
            string middle = "";
            setVals(val, large, middle, word);
            val->left = smallsLeft;
            val->middle = smallsRight;
            val->right = 0;
            large->parent = val->parent;
            large->left = lChild;
            large->middle = rChild;
            // large->right = 0;
            if (val == root){
                root = new Node(middle);
                root->left = val;
                root->middle = large;
                val->parent = root;
                large->parent = root;
                return;
            }
            if (parent->large == ""){
                if (middle < parent->small){
                    parent->large = parent->small;
                    parent->small = middle;
                }else{
                    parent->large = middle;
                }
                parent->right = large;
            }else{
                split(parent, parent->parent, val, large, middle);
            }
        }
    }else{ // first actual split call that's not the root, checks if necessary for recursive split in else statement
        Node* largest = new Node;
        string midVal = "";
        setVals(val, largest, midVal, word);
        if (val == root){
            root = new Node(midVal);
            root->left = val;
            root->middle = largest;
            root->right = 0;
            val->parent = root;
            largest->parent = root;
            return;
        }
        if (parent->large == ""){
            if (parent->left == val){ // assigns children to correct sides for splitting
                if (parent->small < midVal){
                    parent->large = midVal;
                }else{
                    parent->large = parent->small;
                    parent->small = midVal;
                }
                parent->right = parent->middle;
                parent->middle = largest;
                largest->parent = parent;
            }else{
                if (parent->small < midVal){
                    parent->large = midVal;
                }else{
                    parent->large = parent->small;
                    parent->small = midVal;
                }
                parent->right = largest;
                largest->parent = parent;
            }

        }else{ // first recursive call
            split(parent, parent->parent, val, largest, midVal);
        }
    }
}

void Tree::setVals(Node* item, Node* & large, string & middle, const string & word){ // sets smallest, middle, and largest value of split up node
    if (word < item->small){
        middle = item->small;
        item->small = word;
        large->small = item->large;
        item->large = "";
    }else if (word <= item->large){
        middle = word;
        large->small = item->large;
        item->large = "";
    }else{
        large->small = word;
        middle = item->large;
        item->large = "";
    }
}

void Tree::preOrder() const{
    preHelper(root);
    cout << endl;
}

void Tree::preHelper(Node* val) const{
    if (val){
        cout << val->small << ", ";
        preHelper(val->left);
        if (val->large != "")
            cout << val->large << ", ";
        preHelper(val->middle);
        preHelper(val->right);
    }
}

void Tree::inOrder() const{
    inHelper(root);
    cout << endl;
}

void Tree::inHelper(Node* val) const{
    if (val){
        inHelper(val->left);
        cout << val->small << ", ";
        inHelper(val->middle);
        if (val->large != "")
            cout << val->large << ", ";
        inHelper(val->right);
    }
}

void Tree::postOrder() const{
    postHelper(root);
    cout << endl;
}

void Tree::postHelper(Node* val) const{
    if (val){
        postHelper(val->left);
        postHelper(val->middle);
        cout << val->small << ", ";
        postHelper(val->right);
        if (val->large != "")
            cout << val->large << ", ";
    }
}

void Tree::remove(const string & word){
    remove(root, word);
}

void Tree::remove(Node* val, const string & word){
    if (val){
        if (word == val->small || word == val->large){
            // cout << "DID U MAKE IT" << endl;
            if (val == root && !val->left){
                if (val->large == word){
                    val->large = "";
                    return;
                }else if (val->small == word && val->large != ""){
                    val->small = val->large;
                    val->large = "";
                    return;
                }
                delete root;
                root = 0;
                return;
            }
            // cout << "CMON" << endl;
            Node* successor = inorderSucc(val);
            // cout << "YEET" << endl;
            if (successor == val){ // special case if successor is value and the large value exists within the leaf node
                if (val->large != ""){
                val->large = val->small;
                val->large = "";
                return;
                }
            }
            // cout << "PLEASE" << endl;
            if (val->small == word){ // simple swap
                string temp = successor->small;
                successor->small = val->small;
                val->small = successor->small;
            }else if (val->large == word){ // also simple swap
                string temp = val->large;
                val->large = successor->small;
                successor->small = val->large;
            }
            if (successor->large != ""){
                successor->small = successor->large;
                successor->large = "";
            }else{
                successor->small = "";
                fix(successor, successor->parent);
            }
        }else if (word < val->small){ // traverses through to find the node that needs to be removed
            remove(val->left, word);
        }else if (val->large == "" || word <= val->large){
            remove(val->middle, word);
        }else{
            remove(val->right, word);
        }
    }
}

void Tree::fix(Node* successor, Node* parent){
    // cout << "In fix " << endl;
    if (successor == root){
        delete root;
        root = 0;
    }else{
        if ((parent->left->large != "" && parent->left != successor) || (parent->right->large != "" && parent->right != successor) || (parent->middle->large != "" && parent->middle != successor)){
            redistribute(successor, parent); // if children have stuff
        }else{
            merge(successor, parent);
        }
        if (parent->small == ""){
            fix(parent,parent->parent);
        }
    }
    
}

Node* Tree::inorderSucc(Node* val){
    if (val->middle){
        val = val->middle;
    }else{
        if (val->right){
            val = val->right;
        }
    }
    while(val->left){
        val = val->left;
    }
    return val;
}

void Tree::redistribute(Node* successor, Node* parent){
    if ((parent->left && parent->left->large != "") || ((parent->middle && parent->middle->large != "") && parent->right == successor)){ // if the right child is empty
        if (parent->middle->large != ""){
            successor->small = parent->large;
            parent->large = parent->middle->large;
            parent->middle->large = "";
        }else{
            successor->small = parent->large;
            parent->large = parent->middle->small;
            parent->middle->small = parent->small;
            parent->small = parent->left->large;
            parent->left->large = "";
        }
    }else if ((parent->left && parent->left->large != "") || ((parent->right && parent->right->large != "") && parent->middle == successor)){ // if mid child is empty
        if (parent->large == ""){
            successor->small = parent->small;
            parent->small = parent->left->large;
            parent->left->large = "";
        }else if (parent->right->large != ""){
            successor->small = parent->large;
            parent->large = parent->right->small;
            parent->right->small = parent->right->large;
            parent->right->large = "";
        }else{
            successor->small = parent->small;
            parent->small = parent->left->large;
            parent->left->large = "";
        }
    }else if ((parent->middle && parent->middle->large != "")  || ((parent->right && parent->right->large != "") && parent->left == successor)){ // if left child is empty
        if (parent->large == ""){
            successor->small = parent->small;
            parent->small = parent->middle->small;
            parent->middle->small = parent->middle->large;
            parent->middle->large = "";
        }else if (parent->middle->large != ""){
            successor->small = parent->small;
            parent->small = parent->middle->small;
            parent->middle->small = parent->middle->large;
            parent->middle->large = "";
        }else{
            successor->small = parent->small;
            parent->small = parent->middle->small;
            parent->middle->small = parent->large;
            parent->large = parent->right->small;
            parent->right->small = parent->right->large;
            parent->right->large = "";
        }
    }
} 

void Tree::merge(Node* val, Node* parent){
    if (!val->left){
        if (parent->middle == val){ // merges middle
            if (parent->large != ""){
                parent->left->large = parent->small;
                parent->small = parent->large;
                parent->large = "";
                val->small = parent->right->small;
                delete parent->right;
                parent->right = 0;
            }
        }else if (parent->right == val){ // merges right
            if (parent->large != ""){
                parent->middle->large = parent->large;
                parent->large = "";
                delete parent->right;
                parent->right = 0;
            }
        }else{
            if (parent->large != ""){ // merges left
                parent->left->small = parent->small;
                parent->left->large = parent->middle->small;
                parent->middle->small = parent->right->small;
                parent->small = parent->large;
                parent->large = "";
                delete parent->right;
                parent->right = 0;
            }
        }
    }
}

bool Tree::search(const string & word) const{
    string tof = "";
    searchHelper(root, word, tof);
    if (tof == "true"){
        return true;
    }
    return false;
}

void Tree::searchHelper(Node* curr, const string & word, string & val) const{
    if (curr){
        if (curr->small == word || curr->large == word){
            val = "true";
        }
        else{
            if (word < curr->small){
                searchHelper(curr->left, word, val);
            }
            else if (word <= curr->large || curr->large == ""){
                searchHelper(curr->middle, word, val);
            }
            else{
                searchHelper(curr->right, word, val);
            }
        }
    }
}
