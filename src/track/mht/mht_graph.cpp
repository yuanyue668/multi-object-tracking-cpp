#include "mht_graph.h"

Graph::Graph(){

    m_node_list.clear();

    m_max_clique.clear();
    m_dep.clear();
    m_stk.clear();
    m_score_list.clear();
    m_adj_mat.clear();
    m_dej_mat.clear();
    
    max = 0;
}

Graph::Graph(std::vector<VexNode> vex_node_list){

   
    max = 0;

    m_node_list = vex_node_list;
    
    m_node_num = m_node_list.size();

    m_max_clique.clear();
    m_max_clique.resize(m_node_num);

    m_stk.clear();
    m_stk.resize(m_node_num, std::vector<int>(m_node_num));

    m_score_list.clear();
    m_score_list.resize(m_node_num);

    m_dep.clear();
    m_dep.resize(m_node_num);
    m_adj_mat.clear();
    m_dej_mat.clear();
    
    m_adj_mat.resize(m_node_num, std::vector<int>(m_node_num, 0));
    m_dej_mat.resize(m_node_num, std::vector<int>(m_node_num, 1));

    m_vetex_list.clear();
    m_max_clique_list.clear();

    for(int i=0; i < m_node_num; i++){
        for(int j=0; j < m_node_num;j++){
            //assert(vex_node_list[i].path.size() == vex_node_list[j].path.size());
            if(i == j){
                m_dej_mat[i][j]=0;
                m_dej_mat[j][i]=0;
                continue;
            }
            for(int k=0; k < vex_node_list[i].path.size(); k++){
                if(vex_node_list[i].path[k] ==  vex_node_list[j].path[k]){
                   if(vex_node_list[i].path[k] !=0 && vex_node_list[j].path[k] != 0){
                       if(vex_node_list[i].path[k] !=-1 && vex_node_list[j].path[k] != -1){
                            m_adj_mat[i][j] = 1;
                            m_adj_mat[j][i] = 1;
                            m_dej_mat[i][j] = 0;
                            m_dej_mat[j][i] = 0;
                            break;
                       }
                   }
                }

            } 
            
        }
    }

    m_score = 0.0;
}

int Graph::DFS(int n, int ns, int dep, float score){
   
    if(ns == 0){
        if(score > max && m_vetex_list.size() > m_max_clique.size()){
            max = score;
            m_max_clique.clear();
            //std::cout<<"Max clique is : ";
            for(int i=0; i < m_vetex_list.size(); i++){
            //   std::cout<<m_vetex_list[i]<<" ";
               m_max_clique.push_back(m_vetex_list[i]); 
            }
            //std::cout<<std::endl;

        }
        return 1;
    }

    for(int i=0; i<ns; i++){
    //TODO: if the sum of all left node less than current score, save time;
        int k = m_stk[dep][i];
        int cnt = 0;
        float temp_score = 0.0;
        for(int j=i+1; j<ns; j++){
            temp_score += m_node_list[m_stk[dep][j]].score;
        }
        float vetex_score = 0.0;
        for(auto vetex : m_vetex_list){
            vetex_score += m_node_list[vetex].score;
        } 
        if(vetex_score + temp_score < max) return 0;
        std::cout<<"Neb"<< k << ": ";
        if(score + m_score_list[k] < max) return 0;
        //if(dep + n - k <= ) return 0;
        for(int j=i+1; j< ns; j++){
            int p = m_stk[dep][j];
            if(m_dej_mat[k][p]){
                m_stk[dep+1][cnt++] = p;                
            }
            std::cout<<p<<" ";
        }
        if(m_vetex_list.size() + ns < m_max_clique.size()) return 0;
        std::cout<<std::endl;     
        m_vetex_list.push_back(k);
        DFS(n, cnt, dep+1, score+m_node_list[k].score);
        //TODO: if score big than max_score, push back and reset score;
        m_vetex_list.pop_back();
    }
    return 1;
                
}

int Graph::mwis(std::map<int, std::vector<int>>& routes){

    m_max_clique.clear();
    routes.clear();
    int n = m_node_list.size();
    std::cout<<"NUM:"<<n<<std::endl;
    std::vector<std::vector<int>> save_clique; 
    
    double start, end, duration;
    for(int i=n-1; i>=0; i--){
        start = clock();
        ns = 0;
        std::cout<<"Vetex : "<<i<<std::endl;
        std::cout<<"First Neb : ";
        for(int j=i+1; j < n; j++){
            if(m_dej_mat[i][j]){
                std::cout<< j<< " ";
                m_stk[1][ns++] = j;
            }
        }
        std::cout<<std::endl;
        m_vetex_list.push_back(i);
        DFS(n, ns, 1, m_node_list[i].score);
        m_vetex_list.pop_back();
        m_score_list[i] = max;
        end = clock();
        duration = (double)(end - start) / CLOCKS_PER_SEC;
        std::cout<<"Time cost : "<<duration<<" s "<<std::endl;
    }

       
    //for(int i=0;  i <  m_max_clique_list.size(); i++){
    //    float sum = 0.0;
    //    for(auto node : m_max_clique_list[i]){
    //        std::cout<<node<<" ";
    //        sum += m_node_list[node].score;
    //    }
    //    std::cout<<std::endl;
    //    if(sum >= m_score){
    //        if(m_max_clique_list[i].size() > m_max_clique.size()){
    //            m_max_clique = m_max_clique_list[i];
    //            m_score = sum;

    //        }
    //    }
    //    //std::cout<<"---"<<sum;
    //    //std::cout<<std::endl;
    //    ////for(auto node : m_max_clique_list[i]){
    //    //    std::cout<<node<<" ";
    //    //}
    //    //std::cout<<std::endl;
    //}

    for(auto path : m_max_clique){
        std::cout<<path<<" ";
    }
    std::cout<<std::endl;

    for(auto node_index : m_max_clique){
        routes[m_node_list[node_index].id] = m_node_list[node_index].path;
    }

}


int Graph::printGraph(){
   
    std::cout<<"Adj Mat is"<<std::endl;
    for(auto row : m_adj_mat){
           for(auto col : row){
             std::cout<<col<<" ";
           }
           std::cout<<std::endl;
    }

    std::cout<<"Dej Mat is"<<std::endl;
     for(auto row : m_dej_mat){
           for(auto col : row){
             std::cout<<col<<" ";
           }
           std::cout<<std::endl;
    }


}
