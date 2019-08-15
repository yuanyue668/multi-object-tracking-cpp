#include "mht_tree.h"
#include <iostream>
#include <opencv2/core/core.hpp>
#include <memory>
#include <map>
#include <vector>
#include <deque>

Tree::Tree(std::shared_ptr<treeNode> root, int id_, int N)
{
        
    id = id_;
    root_node = root;
    leaf_node.push_back(root);//
    head_node = root;
       
}

int Tree::addNode(std::map<int, std::vector<std::shared_ptr<treeNode>>> dict)
{
    //search the indexes' nodes in leaf_node
    //then add the nodes' children
    std::map< int, std::vector< std::shared_ptr<treeNode> > > ::iterator it;
    it = dict.begin();
    int i, j;
    int level;
    std::vector<std::shared_ptr<treeNode>> search_node;
    while(it!=dict.end())
    {
        
        //traverse in leaf_node
        for(i=0; i<leaf_node.size(); i++)
        {
            if(leaf_node[i]->index==it->first)
            {
                //search_node.push_back(leaf_node[i]);
                level = leaf_node[i]->level;
                leaf_node[i]->children = it->second;
            }
        }
    }
    for(i=0;i<leaf_node.size();i++)
    {
        for(j=0;j<leaf_node[i]->children.size();j++)
        {
            search_node.push_back(leaf_node[i]->children[j]);
        }
        
    }



        it++;
        leaf_node.clear();
        
        for(i=0;i<<search_node.size(); i++)
        {
            leaf_node.push_back(search_node[i]);
            leaf_node[i]->level = level+1;
        }

        /*for(j=0; j<search_node.size(); j++)
        {
            search_node[j]->children = it->second;
            leaf_node = search_node[j]->children;
        }
        it++;*/
        /*
        for(j=0; j<leaf_node[i]->children.size(); j++)
                {
                    search_node.push_back(leaf_node[i]->children[j]);
                    leaf_node[i]->children[j]->parent = leaf_node[i];
                }
                */
         
    
     


}
        
int Tree::pruning(std::map<int, std::vector<int>> route)
{
    //root is static
    //int variable is the index of head_node
    //vector saves the indexes of the nodes on the route
    //int i ,j , count, is_valid;
   // std::vector<int> route_list;
    
    //search for the head_node(if head_node is known, this step is unnesessary)
   /* for(i=0; i<leaf_node.size();i++)
    {
        if(leaf_node[i]->index == route->first){
            head_node = leaf_node[i];
        }
    }*/

    //std::shared_ptr<treeNode> head_node_temp;
    
    //count = 0;
    //delete
    while(head_node->children.size())
    {
        if(head_node>children[0]->index!=route->second[0])
        {
            head_node->children.erase(head_node->children.begin());
        }
    }
    
    head_node = head_node->children[0];

/*

    if(head_node->children.size()>1)
    {
        count++;
        for(i=0;i<head_node->children.size();i++)
        {
            route_list.push_back(i);//is that necessary?
        }

        for(i=0;i<head_node->children.size();i++)
        {
           head_node_temp = head_node->children[i];
           for(j=0;j<head_node_temp->children.size();j++)
           {
                if(head_node_temp->children[j]->index == route->second[count])
                {
                    is_valid++;
                }
           }
           
        }
            
            head_node_temp = route_list[i];
            for(j=0; j<head_node_temp->children.size(); j++)
            {
                if()
            }
            while(head_node_temp->children)
        }
    }*/

}

void Tree::printTree(std::shared_ptr<treeNode> root)
{
    if(root == NULL)
    {
        return;
    }

    int i;
    int current_level = 1;
    std::cout<<"[";

    std::deque<std::shared_ptr<treeNode>> queue_tree_node;
    queue_tree_node.push_back(root);
   
    while(queue_tree_node.size())
    {
        
        std::shared_ptr<treeNode> temp_node = queue_tree_node.front();
        queue_tree_node.pop_front();

        if(temp_node->level>current_level){
            std::cout<<std::endl;
            std::cout<<"[";
            current_level = temp_node->level;
        }
        //print tree
        std::cout<<temp_node->index;
        
        if(queue_tree_node.size()==0 || temp_node->parent!=queue_tree_node[0]->parent)
        {
            std::cout<<"]";
        }

        for(i=0;i<temp_node->children.size();i++){
            if(temp_node->children[i]){
                queue_tree_node.push_back(temp_node->children[i]);
            }
        }
    }
    std::cout<<std::endl;
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
