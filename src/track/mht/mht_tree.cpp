#include "mht_tree.h"
#include <iostream>
#include <opencv2/core/core.hpp>
#include <memory>
#include <map>
#include <vector>

Tree::Tree(std::shared_ptr<treeNode> root, int i, int n)
{
        
    id = i;
    root_node = root;
    leaf_node.push_back(root);//
    head_node = root;
    N = n;
       
}

int Tree::addNode(std::map<int, std::vector<std::shared_ptr<treeNode>>> dict)
{
    //search the indexes' nodes in leaf_node
    //then add the nodes' children
    std::map<int, std::vector<std::shared_ptr<treeNode>>>::iterator it;
    it = dict.begin();
    std::vector<std::shared_ptr<treeNode>> sub_children_node;
    while(it!=dict.end())
    {
        leaf_node[it->first]->children = it->second;
        for(int i=0;i<it->second.size();i++){
            it->second[i]->parent = leaf_node[it->first]; 
        }
        it++;
        // leaf_node.clear();
        // 
        // for(i=0;i<leaf_node.size(); i++)
        // {
        //     leaf_node.push_back(search_node[i]);
        //     leaf_node[i]->level++;
        // }
         /*for(j=0; j<search_node.size(); j++)
         {
             search_node[j]->children = it->second;
             leaf_node = search_node[j]->children;
         }
         it++;*/
    }
    sub_children_node.clear();
    for(int i=0;i<leaf_node.size();i++){
        for(int j=0;j<leaf_node[i]->children.size();j++){
            sub_children_node.push_back(leaf_node[i]->children[j]);
        }
    }
    leaf_node = sub_children_node; 


}
        
int Tree::pruning()
{

}

int Tree::printTree(std::shared_ptr<treeNode> root)
{
    int i;
    if(root != NULL){
        //std::cout<<"Tree"<<std::endl;
        std::cout<<"[";
        for(i=0;i<root->children.size();i++)
        {
            std::cout<<root->children[i]->index<<" ";
        }
        std::cout<<"]";
        // std::cout<<std::endl;
        // for(i=0;i<root->children.size();i++){
        //     printTree(root->children[i]);
        // }
    }
    
}

int Tree::getN(){
    return N;
}

int Tree::getId()
{
    return id;
}

std::shared_ptr<treeNode> Tree::getRoot()
{
    return root_node;
}

std::shared_ptr<treeNode> Tree::getHead()
{
    return head_node;
}

std::vector<std::shared_ptr<treeNode>> Tree::getLeafNode()
{
    return leaf_node;
}
