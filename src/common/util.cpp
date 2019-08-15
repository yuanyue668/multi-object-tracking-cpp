#include "util.h"
#include "mht_tree.h"


/*
 *===================================
 *  Tree convert to Graph
 *
 *===================================
*/

int preorderTraversal(treeNode tree_node, std::vector<int>& path, 
                std::vector<std::vector<int>>& path_list){
    
    path.push_back(tree_node.index);
    if(tree_node.children.size() == 0){
        path_list.push_back(path);
    }else{
        for(int i=0; i < tree_node.children.size(); i++){
            preorderTraversal(*(tree_node.children[i]), path, path_list);
            path.pop_back();
        }
    }

}

int backTraversal(treeNode tree_node, std::shared_ptr<treeNode> head_node,
         std::vector<int>& path, std::vector<std::vector<int>>& path_list, int N){
    path.push_back(tree_node.index);
    
    /*When the depth of the tree is not big than N*/
    if(tree_node.parent == head_node){
        path.push_back(tree_node.parent->index);
        if(path.size() < N){
            for(int i=N-path.size();i>0;i--){
                path.push_back(0);
            }
        }
        path_list.push_back(path);
        return 1;
    }
   /*When this node is a root node*/
    if(tree_node.parent == NULL &&  path.size() < N){
        
        for(int i=N-path.size(); i > 0; i--){
            path.push_back(0);
        }
        path_list.push_back(path);
        return 1;

    }
    if(tree_node.parent != NULL){

        backTraversal(*(tree_node.parent), head_node, path, path_list, N);
    }
}

int TreeToGraph(std::vector<Tree> tree_list, Graph& graph){

    std::vector<int> path; 
    std::vector<std::vector<int>> path_list;

    for(auto tree : tree_list){
        
        std::cout<<"Tree No."<<tree.getId()<<std::endl;
        //preorderTraversal(tree.getHead(),path, path_list);
        for(auto leaf : tree.getLeafNode()){
        
            path.clear();
            backTraversal(*(leaf), tree.getHead(), path, path_list, tree.getN());
        }
    }
    std::cout<<"graph node size is "<<path_list.size()<<std::endl;
    std::vector<VexNode> graph_node_list;
    for(auto path : path_list){
        VexNode graph_node;
        graph_node.path.clear();
        for(int i = path.size()-1; i >=0; i--){
            std::cout<<path[i]<<" ";
            graph_node.path.push_back(path[i]);
        }
        std::cout<<std::endl;
        graph_node_list.push_back(graph_node);
    }
    graph = Graph(graph_node_list);
}


/*
 *===================================
 * Test Unit 
 *
 *===================================
*/

int test_graph(){
    std::vector<VexNode> vex_node_list;
    VexNode temp_node = {1.0, {1,3,4}};
    vex_node_list.push_back(temp_node);
    
    temp_node = {1.0, {1,3,2}};
    vex_node_list.push_back(temp_node);
    
    temp_node = {1.0, {1,2,1}};
    vex_node_list.push_back(temp_node);
    
    temp_node = {1.0, {1,2,3}};
    vex_node_list.push_back(temp_node);
    
    temp_node = {1.0, {2,2,1}};
    vex_node_list.push_back(temp_node);
    
    temp_node = {1.0, {2,2,3}};
    vex_node_list.push_back(temp_node);
    
    temp_node = {1.0, {2,1,0}};
    vex_node_list.push_back(temp_node);
    
    temp_node = {1.0, {0,0,5}};
    vex_node_list.push_back(temp_node);
    
    Graph A(vex_node_list);
    A.printGraph();
    A.mwis();
}

int test_treeTograph(){

    /*Fake Tree No.1*/
    treeNode root = {{10,9,8,7},6,1,1,NULL};
    std::shared_ptr<treeNode> root_ptr(new treeNode(root));

    Tree test_tree(root_ptr,1,3);

    treeNode node_a = {{10,9,8,7},6,2,3,root_ptr};
    treeNode node_b = {{10,9,8,7},6,2,2,root_ptr};

    std::shared_ptr<treeNode> node_a_ptr(new treeNode(node_a));
    std::shared_ptr<treeNode> node_b_ptr(new treeNode(node_b));
    
    treeNode node_c = {{10,9,8,7},6,3,4,node_a_ptr};
    treeNode node_d = {{10,9,8,7},6,3,2,node_a_ptr};
    treeNode node_e = {{10,9,8,7},6,3,1,node_b_ptr};
    treeNode node_f = {{10,9,8,7},6,3,3,node_b_ptr};
    
    std::shared_ptr<treeNode> node_c_ptr(new treeNode(node_c));
    std::shared_ptr<treeNode> node_d_ptr(new treeNode(node_d));
    std::shared_ptr<treeNode> node_e_ptr(new treeNode(node_e));
    std::shared_ptr<treeNode> node_f_ptr(new treeNode(node_f));
    

    std::vector<std::shared_ptr<treeNode>> node_list;
    std::map<int, std::vector<std::shared_ptr<treeNode>>> dict;
    
    node_list.push_back(node_a_ptr);
    node_list.push_back(node_b_ptr);
    
    dict[0] = node_list;
    test_tree.addNode(dict);
    
    node_list.clear();
    node_list.push_back(node_c_ptr);
    node_list.push_back(node_d_ptr);
    dict[0] = node_list;

    node_list.clear();
    node_list.push_back(node_e_ptr);
    node_list.push_back(node_f_ptr);
    dict[1] = node_list;

    test_tree.addNode(dict);

    dict.clear();
   
    /*Fake Tree No.2*/
    treeNode root_2 = {{10,9,8,7},6,1,2,NULL};
    std::shared_ptr<treeNode> root_2_ptr(new treeNode(root_2));

    Tree test_tree_2(root_2_ptr,2,3);

    treeNode node_2_a = {{10,9,8,7},6,2,2,root_2_ptr};
    treeNode node_2_b = {{10,9,8,7},6,2,1,root_2_ptr};

    std::shared_ptr<treeNode> node_2_a_ptr(new treeNode(node_2_a));
    std::shared_ptr<treeNode> node_2_b_ptr(new treeNode(node_2_b));
    
    treeNode node_2_c = {{10,9,8,7},6,3,1,node_2_a_ptr};
    treeNode node_2_d = {{10,9,8,7},6,3,3,node_2_a_ptr};
    treeNode node_2_e = {{10,9,8,7},6,3,0,node_2_b_ptr};
    
    std::shared_ptr<treeNode> node_2_c_ptr(new treeNode(node_2_c));
    std::shared_ptr<treeNode> node_2_d_ptr(new treeNode(node_2_d));
    std::shared_ptr<treeNode> node_2_e_ptr(new treeNode(node_2_e));

    node_list.clear();
    
    node_list.push_back(node_2_a_ptr);
    node_list.push_back(node_2_b_ptr);
    
    dict[0] = node_list;
    test_tree_2.addNode(dict);
    
    node_list.clear();
    node_list.push_back(node_2_c_ptr);
    node_list.push_back(node_2_d_ptr);
    dict[0] = node_list;

    node_list.clear();
    node_list.push_back(node_2_e_ptr);
    dict[1] = node_list;

    test_tree_2.addNode(dict);

    /*Fake Tree No.3*/
    treeNode root_3 = {{10,9,8,7},6,1,5,NULL};
    std::shared_ptr<treeNode> root_3_ptr(new treeNode(root_3));

    Tree test_tree_3(root_3_ptr,3,3);

    //map<int, vector<std::shared_ptr<treeNode>>>:: iterator it;
    //dict.insert(pair<int, std::vector<std::shared_ptr<treeNode>>> 1,testTree);
    //test_tree.printTree(root_ptr);
    //test_tree(root1,1,3);
    //printf("")
    // std::cout<<"id:"<<test_tree.getId()<<std::endl;
    //std::cout<<"root_node:"<<test_tree.getRoot()<<std::endl;
    //std::cout<<"root_node:"<<test_tree.getRoot()<<std::endl;
    // std::cout<<"leaf_node:"<<&(test_tree.getLeafNode()[0])<<std::endl;
    // std::cout<<"head_node:"<<test_tree.getHead()<<std::endl;
    // std::cout<<"box:"<<test_tree.getRoot()->box<<std::endl;
    //test_tree.printTree(root_ptr);
    std::vector<Tree> tree_list;
    tree_list.push_back(test_tree);
    tree_list.push_back(test_tree_2);
    tree_list.push_back(test_tree_3);
    Graph graph;
    TreeToGraph(tree_list, graph);
    graph.printGraph();
    graph.mwis();
}


int test_tree(){

    treeNode root = {{10,9,8,7},6,2,1,NULL};
    std::shared_ptr<treeNode> root_ptr(new treeNode(root));

    treeNode root_a = {{10,9,8,7},6,2,1,root_ptr};
    treeNode root_b = {{10,9,8,7},6,2,2,root_ptr};
    treeNode root_c = {{10,9,8,7},6,2,3,root_ptr};
    treeNode root_d = {{10,9,8,7},6,2,4,root_ptr};

    std::shared_ptr<treeNode> root_a_ptr(new treeNode(root_a));
    std::shared_ptr<treeNode> root_b_ptr(new treeNode(root_b));
    std::shared_ptr<treeNode> root_c_ptr(new treeNode(root_c));
    std::shared_ptr<treeNode> root_d_ptr(new treeNode(root_d));

    std::vector<std::shared_ptr<treeNode>> node_list;

    node_list.push_back(root_a_ptr);
    node_list.push_back(root_b_ptr);
    node_list.push_back(root_c_ptr);
    node_list.push_back(root_d_ptr);

    std::map<int, std::vector<std::shared_ptr<treeNode>>> dict;
    dict[0] = node_list;
    //map<int, vector<std::shared_ptr<treeNode>>>:: iterator it;
    //dict.insert(pair<int, std::vector<std::shared_ptr<treeNode>>> 1,testTree);
    
    Tree test_tree(root_ptr,1,3);
    //test_tree(root1,1,3);
    //printf("")
    // std::cout<<"id:"<<test_tree.getId()<<std::endl;
    //std::cout<<"root_node:"<<test_tree.getRoot()<<std::endl;
    //std::cout<<"root_node:"<<test_tree.getRoot()<<std::endl;
    // std::cout<<"leaf_node:"<<&(test_tree.getLeafNode()[0])<<std::endl;
    // std::cout<<"head_node:"<<test_tree.getHead()<<std::endl;
    // std::cout<<"box:"<<test_tree.getRoot()->box<<std::endl;
    
    
    test_tree.addNode(dict);
    test_tree.printTree(root_ptr);

}
