#pragma once


template<typename T>
class BSTree
{
    template<typename U>
    class TreeNode;

public:
    BSTree() = default;
    ~BSTree() = default;

    void insert(const T& value)
    {
        if (m_head == nullptr)
        {
            m_head = new TreeNode<T>{value};
            return;
        }

        recursiveInsert(nullptr, m_head, value);
    }

    void preorder()
    {
        _preorder(m_head);
    }

    void inorder()
    {
        _inorder(m_head);
    }

    void postorder()
    {
        _postorder(m_head);
    }

    void remove(const T& value)
    {
    }

    TreeNode<T>* find(const T& value)
    {
        if (m_head == nullptr)
        {
            return nullptr;
        }

        return _find(m_head, value);
    }

    size_t size() const { return m_size; }

private:

    void _preorder(TreeNode<T>* node)
    {
        if (node == nullptr)
            return;

        cout << node->value << endl;
        _preorder(node->left);
        _preorder(node->right);
    }

    void _inorder(TreeNode<T>* node)
    {
        if (node == nullptr)
            return;

        _inorder(node->left);
        cout << node->value << endl;
        _inorder(node->right);
    }

    void _postorder(TreeNode<T>* node)
    {
        if (node == nullptr)
            return;

        _postorder(node->left);
        _postorder(node->right);
        cout << node->value << endl;
    }

    TreeNode<T>* _find(TreeNode<T>* node, const T& value)
    {
        if (node == nullptr)
        {
            return nullptr;
        }

        if (value == node->value)
        {
            return node;
        }

        if (value < node->value)
        {
            return _find(node->left, value);
        }
        else if (value > node->value)
        {
            return _find(node->right, value);
        }
    }

    void recursiveInsert(TreeNode<T>** parentNode, TreeNode<T>* node, const T& value)
    {
        if (node == nullptr)
        {
            *parentNode = new TreeNode<T>{value};
            return;
        }

        if (value < node->value)
        {
            recursiveInsert(&node->left, node->left, value);
        }
        else if (value > node->value)
        {
            recursiveInsert(&node->right, node->right, value);
        }

        // discard this value since we only keep
        // unique values in the tree
    }

private:
    template<typename U>
    struct TreeNode
    {
        T value;
        TreeNode<U>* left{nullptr};
        TreeNode<U>* right{nullptr};
    };
    
private:
    TreeNode<T>* m_head{nullptr};
    size_t m_size{0};
};