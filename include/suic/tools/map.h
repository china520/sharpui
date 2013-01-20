

#ifndef __UIMAP_H
#define __UIMAP_H

#include "rbtree.h"
#include <suic/core/uiobject.h>

namespace suic
{

template<typename KEY,typename VAL, typename BASE=suic::Object>
class Map : public _rbtree<KEY, VAL, BASE>
{
public:

    typedef unsigned int size_type;
    typedef Map<KEY, VAL> Myt;

    struct _RBNode
    {
        _RBNode* _parent;
        RBNode* _node;

        _RBNode() : _node(NULL), _parent(NULL) {}
        _RBNode(RBNode* n) : _node(n), _parent(NULL) {}
    };

    struct iterator
    {
        Myt* _this;
        RBNode* _node;
        _RBNode* _stack;

        iterator()
        {
            _stack = NULL;
            _node = NULL;
            _this = NULL;
        }

        ~iterator()
        {
            while (_stack != NULL)
            {
                _RBNode* p = _stack->_parent;

                delete _stack;
                _stack = p;
            }
        }

        iterator(iterator& Other)
        {
            _this = Other._this;
            _node = Other._node;
            _stack = Other._stack;
            Other._stack = NULL;
        }

        iterator& operator=(iterator& Other)
        {
            _this = Other._this;
            _node = Other._node;
            _stack = Other._stack;
            Other._stack = NULL;

            return *this;
        }

        RBNode* operator->()
        {
            return _node;
        }

        KEY& operator*()
        {
            return _node->first;
        }

        bool operator!=(const iterator& Other)
        {
            return (Other._node != _node);
        }

        bool operator==(const iterator& Other)
        {
            return (Other._node == _node);
        }

        void operator++()
        {
            // 
            // 左边未遍历
            //
            if (_this->IsNullNode(_node->left))
            {
                RBNode* tmnode = _stack->_node;
                _RBNode* sp = _stack->_parent;

                delete _stack;
                _stack = sp;

                while (_this->IsNullNode(_node=tmnode->right) && NULL != _stack)
                {
                    tmnode = _stack->_node;

                    sp = _stack->_parent;

                    delete _stack;
                    _stack = sp;
                }

                if (!_this->IsNullNode(_node))
                {
                    _RBNode* tm = _stack;

                    _stack = new _RBNode(_node);
                    _stack->_parent = tm;
                }
            }
            else
            {
                _node = _node->left;

                _RBNode* tm = _stack;

                _stack = new _RBNode(_node);
                _stack->_parent = tm;
            }
        }
    };

    Map()
    {
        _end._node = _nullNode;
        _end._this = this;
    }

    virtual ~Map()
    {
    }

    iterator begin()
    {
        iterator iter;

        iter._this = this;
        iter._node = GetRootNode();

        // left为当前遍历节点
        // right用来存储遍历过的节点
        iter._stack = new _RBNode();
        iter._stack->_node = iter._node;
        iter._stack->_parent = NULL;

        return iter;
    }

    iterator & end()
    {
        _end._node = _nullNode;
        return _end;
    }

    size_type size() const
    {
        return (size_type)_iSize;
    }

    iterator& find(KEY k)
    {
        _cur._node = Find(k);
        return _cur;
    }

    VAL& operator[](KEY k)
    {
        RBNode* newnode = Insert(k);
        return newnode->second;
    }

    void insert(KEY k, VAL v)
    {
        Insert(k, v);
    }

    void erase(KEY k)
    {
        Delete(k);
    }

    void erase(iterator iter)
    {
        Delete(iter._node->first);
    }

    void clear()
    {
        Clear();
    }

protected:

    iterator _end;
    iterator _cur;
};

template <typename KEY>
class Set : public Map<KEY,KEY>
{
public:

    Set()
    {
    }

    virtual ~Set()
    {
    }

    size_type count(KEY k)
    {
        if (IsNullNode(Find(k)))
        {
            return 0;
        }
        else
        {
            return 1;
        }
    }

    void insert(KEY k)
    {
        __super::insert(k, k);
    }
};

}

#endif
