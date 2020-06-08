#pragma once

#include <string>

static constexpr int SIZE = 26;
struct TrieNode
{
    TrieNode()
    {
        for (int i = 0; i < SIZE; ++i)
            children[i] = nullptr;
        isWordEnd = false;
    }

    ~TrieNode()
    {
        for (int i = 0; i < SIZE; ++i)
            if (children[i])
                delete children[i];
    }

    TrieNode* children[SIZE];
    bool isWordEnd = false;
};

// Trie is a DS for strings
class Trie
{ 
public:
    Trie()
    {
        m_root = new TrieNode();
    }

    ~Trie()
    {
        delete m_root;
    }

    void insert(const std::string& val) // inserts only if not present, if it is a prefix of another node, just mark it as a possible full-word
    {
        TrieNode* current = m_root;
        for (size_t level = 0; level < val.length(); ++level)
        {
            int idx = val.at(level) - 'a';
            if (!current->children[idx])
                current->children[idx] = new TrieNode();
        
            current = current->children[idx];
        }

        // mark it as a leaf
        current->isWordEnd = true;
    }

    bool search(const std::string& val) const
    {
        TrieNode* current = m_root;
        for (size_t level = 0; level < val.length(); ++level)
        {
            int idx = val.at(level) - 'a'; // only lower-case ASCII strings stored in this trie

            if (!current->children[idx])
                return false;

            current = current->children[idx];
        }
        return (current && current->isWordEnd); // returns true only if this was marked before as a word and it exists
    }

    // add removal?
private:

    TrieNode* m_root;
};