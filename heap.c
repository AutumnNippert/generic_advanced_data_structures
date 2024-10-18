#include "heap.h"

heap_t* heap_create(size_t type_size, compare_t compare, free_t free){
    heap_t* new = calloc(1, sizeof(heap_t));
    new->size = 0;
    new->type_size = type_size;
    new->compare_func = compare;
    new->free_func = free;
    return new;
}

static heap_node_t* heap_node_create(void* val){
    heap_node_t* new = calloc(1, sizeof(heap_node_t));
    new->val = val;
    new->parent = NULL;
    new->left = NULL;
    new->right = NULL;
    return new;
}

static void heap_increase_key(heap_t* heap, heap_node_t* node, void* val){
    if(heap->compare_func(node->val, val) >= 0){
        return;
    }
    node->val = val;
    while(node != heap->root && heap->compare_func(node->val, node->parent->val) > 0){
        void* temp = node->val;
        node->val = node->parent->val;
        node->parent->val = temp;
        node = node->parent;
    }
}

static void heap_extract(heap_t* heap, heap_node_t* node){
    if(node->left == NULL && node->right == NULL){
        if(node == heap->root){
            heap->root = NULL;
            return;
        }
        if(node->parent->left == node){
            node->parent->left = NULL;
        }
        else{
            node->parent->right = NULL;
        }
        return;
    }
    if(node->left == NULL){
        heap_extract(heap, node->right);
        return;
    }
    if(node->right == NULL){
        heap_extract(heap, node->left);
        return;
    }
    if(heap->compare_func(node->left->val, node->right->val) > 0){
        heap_extract(heap, node->left);
    }
    else{
        heap_extract(heap, node->right);
    }
}

void heap_push(heap_t* heap, void* val){
    heap_node_t* new = heap_node_create(val);
    heap->size++;
    if(heap->root == NULL){
        heap->root = new;
        return;
    }
    heap_node_t* curr = heap->root;
    size_t size = heap->size;
    while(size > 1){
        if(size % 2 == 0){
            if(curr->left == NULL){
                curr->left = new;
                new->parent = curr;
                heap_increase_key(heap, new, val);
                return;
            }
            curr = curr->left;
        }
        else{
            if(curr->right == NULL){
                curr->right = new;
                new->parent = curr;
                heap_increase_key(heap, new, val);
                return;
            }
            curr = curr->right;
        }
        size /= 2;
    }
}

void* heap_peek(heap_t* heap){
    return heap->root->val;
}

void* heap_pop(heap_t* heap){
    void* val = heap->root->val;
    heap_node_t* last = heap->root;
    heap->size--;
    if(heap->size == 0){
        heap->root = NULL;
        return val;
    }
    heap_node_t* curr = heap->root;
    size_t size = heap->size;
    while(size > 1){
        if(size % 2 == 0){
            curr = curr->left;
        }
        else{
            curr = curr->right;
        }
        size /= 2;
    }
    heap->root->val = curr->val;
    heap_extract(heap, curr);
    return val;
}

void heap_free(heap_t* heap){
    free(heap);
}