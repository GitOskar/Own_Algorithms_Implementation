#include <iostream>

#define RED false
#define BLACK true

using namespace std;

struct Node
{
    string key;
    bool colour;
    Node* smaller_son;
    Node* bigger_son;
    Node* father;

    Node(string key) : key(key), colour(RED), smaller_son(nullptr), bigger_son(nullptr), father(nullptr) {}
};

class Set
{
    Node* root;
    unsigned int count;

public:
    Set();
    void insert(string key);
    unsigned int size();

private:
    void restore_red_and_black(Node* node);
    bool uncle(Node * node);
    void rotate_left_with_colour(Node* node);
    void rotate_right_with_colour(Node* node);
    void rotate_left_without_colour(Node* node);
    void rotate_right_without_colour(Node* node);

};

Set::Set()
{
    count = 0;
    root = nullptr;
}

void Set::insert(string key)
{
    if (root == nullptr)
    {
        root = new Node(key);
        root->colour = BLACK;
        count++;
        return;
    }

    Node* tmp = root;

    while (true)
    {
        if (tmp->key == key)
            return;
        if (tmp->key > key)
        {
            if (tmp->smaller_son != nullptr)
            {
                tmp = tmp->smaller_son;
            }
            else
            {
                tmp->smaller_son = new Node(key);
                tmp->smaller_son->father = tmp;
                tmp = tmp->smaller_son;
                count++;
                break;
            }
        }
        else
        {
            if (tmp->bigger_son != nullptr)
            {
                tmp = tmp->bigger_son;
            }
            else
            {
                tmp->bigger_son = new Node(key);
                tmp->bigger_son->father = tmp;
                tmp = tmp->bigger_son;
                count++;
                break;
            }
        }
    }

    restore_red_and_black(tmp);
}

unsigned int Set::size()
{
    return count;
}

void Set::restore_red_and_black(Node *node)
{
    if (node == root)
    {
        root->colour = BLACK;
        return;
    }

    //if everything is good
    if (node->father->colour == BLACK)
        return;

    //if not

    bool uncle_colour = uncle(node);

    if (uncle_colour == RED)
    {
        //recolour, uncle is already red
        node->colour = RED;
        node->father->colour = BLACK;
        node->father->father->colour = RED;
        restore_red_and_black(node->father->father);
    }
    else //uncle is black
    {
        //is father a left son
        if (node->father->father->smaller_son == node->father)
        {
            //is node a left son?
            if (node->father->smaller_son == node)
            {
                //in line
                node = node->father;

                rotate_left_with_colour(node);
            }
            else //node is a right son
            {
                //in triangle
                rotate_right_without_colour(node);

                //in line
                rotate_left_with_colour(node);
            }
        }
        else //father is right son
        {
            //is node a right son?
            if (node->father->bigger_son == node)
            {
                node = node->father;

                rotate_right_with_colour(node);
            }
            else//node is left son
            {
                //in triangle
                rotate_left_without_colour(node);

                //in line
                rotate_right_with_colour(node);
            }
        }
    }
}

bool Set::uncle(Node *node)
{
    if (node->father->father->smaller_son == node->father)
    {
        if(node->father->father->bigger_son == nullptr || node->father->father->bigger_son->colour == BLACK)
        {
            return BLACK;
        }
        else
        {
            node->father->father->bigger_son->colour = BLACK;
            return RED;
        }
    }
    else //father was bigger son
    {
        if(node->father->father->smaller_son == nullptr || node->father->father->smaller_son->colour == BLACK)
        {
            return BLACK;
        }
        else
        {
            node->father->father->smaller_son->colour = BLACK;
            return RED;
        }
    }
}

void Set::rotate_right_with_colour(Node *node)
{
    rotate_right_without_colour(node);

    if (node->smaller_son->colour == RED)
        node->smaller_son->colour = BLACK;
    else
        node->smaller_son->colour = RED;

    if (node->colour == RED)
        node->colour = BLACK;
    else
        node->colour = RED;

    if (node->smaller_son == root)
    {
        root = node;
    }
}

void Set::rotate_left_with_colour(Node *node)
{
    rotate_left_without_colour(node);

    if (node->bigger_son->colour == RED)
        node->bigger_son->colour = BLACK;
    else
        node->bigger_son->colour = RED;

    if (node->colour == RED)
        node->colour = BLACK;
    else
        node->colour = RED;

    if (node->bigger_son == root)
    {
        root = node;
    }
}

void Set::rotate_left_without_colour(Node *node)
{
    if (node->father->father != nullptr) //probably not necessary case
    {
        if (node->father->father->bigger_son == node->father)
            node->father->father->bigger_son = node;
        else
            node->father->father->smaller_son = node;
    }
    node->father->smaller_son = node->bigger_son;
    if (node->bigger_son != nullptr)
        node->bigger_son->father = node->father;
    node->bigger_son = node->father;
    node->father = node->bigger_son->father;
    node->bigger_son->father = node;
}

void Set::rotate_right_without_colour(Node *node)
{
    if (node->father->father != nullptr) //probably not necessary case
    {
        if (node->father->father->bigger_son == node->father)
            node->father->father->bigger_son = node;
        else
            node->father->father->smaller_son = node;
    }
    node->father->bigger_son = node->smaller_son;
    if (node->smaller_son != nullptr)
        node->smaller_son->father = node->father;
    node->smaller_son = node->father;
    node->father = node->smaller_son->father;
    node->smaller_son->father = node;
}

int main()
{
    ios::sync_with_stdio(false);

    unsigned int count, lenghtOfSubStr;
    string margedString = "", tmp;
    margedString.reserve(sizeof(unsigned int));
    cin >> count >> lenghtOfSubStr;

    for (unsigned int i=0 ; i<count ; i++)
    {
        cin >> tmp;
        margedString += tmp;
    }

    unsigned int outOfString = margedString.length() - lenghtOfSubStr + 1;
    Set wordsWithoutDuplicates;

    for (unsigned int beginOfSubStr=0 ; beginOfSubStr<outOfString ; beginOfSubStr++)
        wordsWithoutDuplicates.insert( margedString.substr(beginOfSubStr, lenghtOfSubStr) );

    cout << wordsWithoutDuplicates.size();

    return 0;
}
