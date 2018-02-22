#coding=utf-8
import numpy as np
import scipy.sparse as sp
import heapdict

class Graph:
    def __init__(self):
        """ Initialize with an empty edge dictionary. """
        self.edges = {}
    
    def add_edges(self, edges_list):
        all_nodes=[]
        for i in edges_list:
            all_nodes.append(i[0])
            all_nodes.append(i[1])
            if i[0] in self.edges.keys():
                self.edges[i[0]][i[1]]=1
            else:
                self.edges[i[0]]={i[1]:1}

        if(len(edges_list)>1):
            self.nodes=list(set(all_nodes))
            self.node_num=len(self.nodes)
        else:
            self.nodes=list(set(all_nodes))
            self.node_num=1

        for i in self.nodes:
            if i not in self.edges.keys():
                self.edges[i]={}
        """ Add a list of edges to the network. Use 1.0 to indiciate the presence of an edge. 
        
        Args:enc
            edges_list: list of (a,b) tuples, where a->b is an edge to add
        """
        pass
        
    def shortest_path(self, source):
        v0=source
        INF=np.inf
        book=set()
        minv=v0
        dis=dict((k,INF) for k in self.nodes)
        path=dict((k,None) for k in self.nodes)
        dis[v0]=0
        while len(book)<len(self.edges):
            book.add(minv)
            if minv not in self.edges.keys():
                #print "this node has no out"
                pass
            else:
                #print self.edges[minv]
                for w in self.edges[minv]:
                    if(dis[minv]+self.edges[minv][w]<dis[w]):
                        path[w]=minv
                        dis[w]=dis[minv]+self.edges[minv][w]
            new=INF
            for v in dis.keys():
                if v in book:
                    continue
                if dis[v]<new:
                    new=dis[v]
                    minv=v
            #----------------------------------------modified
            if new==INF:
                break
        return dis,path
        """ Compute the single-source shorting path.
        
        This function uses Djikstra's algorithm to compute the distance from 
        source to all other nodes in the network.
        
        Args:
            source: node index for the source
            
        Returns: tuple: dist, path
            dist: dictionary of node:distance values for each node in the graph, 
                  where distance denotes the shortest path distance from source
            path: dictionary of node:prev_node values, where prev_node indicates
                  the previous node on the path from source to node
        """
        pass
    
        
    def adjacency_matrix(self):
        self.name={}
        index=0
        for i in self.nodes:
            self.name[i]=index
            index+=1
        #为每个节点名生成int索引
        ax=np.array([])
        ay=np.array([])
        data=np.array([])
        length=self.node_num


        for i in self.edges.items():
            for j in i[1].items():
                ax=np.append(ax,self.name[j[0]])
                ay=np.append(ay,self.name[i[0]])
                data=np.append(data,j[1])
        self.cm=sp.coo_matrix((data, (ax, ay)), dtype=int ,shape=(length,length))#构建稀疏阵

        """ Compute an adjacency matrix form of the graph.  
        
        Returns: tuple (A, nodes)
            A: a sparse matrix in COO form that represents the adjaency matrix
               for the graph (i.e., A[j,i] = 1 iff there is an edge i->j)
               NOTE: be sure you have this ordering correct!
            nodes: a list of nodes indicating the node key corresponding to each
                   index of the A matrix
        """
        pass
    def pagerank2(self,d=0.85,iters=100):
        pm=np.array((self.cm.toarray()),dtype=float)
        length=len(pm)
        #def share(a,length):
        sumlist=pm.sum(axis=0)
        for i in range(length):#col i
            for j in range(length):#row j
                if(sumlist[i]==0):
                    pm[j][i]=1.0/length
                else:
                    pm[j][i]/=sumlist[i]
        pm=(d)*pm+(1-d)/pm.shape[0]*np.ones(pm.shape)
        x=1.0/length*np.ones((length,1))

        for i in range(iters):
            x=np.dot(pm,x)

        dicrank={}

        for i in self.nodes:
            dicrank[i]=x[self.name[i]][0]
        #print dicrank
        return dicrank

    def pagerank(self, d=0.85, iters=100):

        pm=self.cm
        length=self.node_num
        sumlist=[]
        t_row=pm.row
        t_col=pm.col
        t_data=np.array(pm.data,dtype=float)

        t=(pm.sum(axis=0)).tolist()
        for i in range(length):
            sumlist.append(t[0][i])
 
        nodelist=[]
        for i in range(len(t_row)):
            nodelist.append((pm.row[i],pm.col[i]))

        for i in range(length):#col i
            if sumlist[i]==0:
                for j in range(length):
                    t_row= np.append(t_row,j)
                    t_col= np.append(t_col,i)
                    t_data=np.append(t_data,1.0/length)
            else:
                for j in range(length):#row j
                    if tuple((j,i)) in nodelist:

                        p=nodelist.index(tuple((j,i)))
                        t_data[p]=float(t_data[p]/sumlist[i])

        pm=sp.coo_matrix((t_data, (t_row, t_col)), dtype=float ,shape=(length,length))
        #print pm
        pm=(d)*pm+(1-d)/pm.shape[0]*np.ones(pm.shape)
        x=1.0/length*np.ones((length,1))

        for i in range(iters):
            x=np.dot(pm,x)

        dicrank={}

        for i in self.nodes:
            dicrank[i]=(x[self.name[i]].tolist())[0][0]
        #print dicrank
        return dicrank
        '''
        for i in range(100):
            share(pm,length)
            pm=(1-d)*pm+d/pm.shape[0]*np.ones(pm.shape)
            print pm
        print pm
        '''
        '''
        x = np.ones(A.shape[0])/A.shape[0]
        for _ in range(T):
            x = pm @ x
            x = x/x.sum()
        print(x)
        '''
        """ Compute the PageRank score for each node in the network.
        
        Compute PageRank scores using the power method.
        
        Args:
            d: 1 - random restart factor
            iters: maximum number of iterations of power method
            
        Returns: dict ranks
            ranks: a dictionary of node:importance score, for each node in the
                   network (larger score means higher rank)
        
        """
        pass
            
# HANDOUT_END
edgelist=[(1,2,{'weight':100}),(2,3,{'weight':100}),(3,6,{'weight':100}),(6,9,{'weight':100}),(1,5,{'weight':1000}),(5,9,{'weight':1000}),(1,4,{'weight':100}),(4,7,{'weight':100}),(7,8,{'weight':100}),(8,9,{'weight':200})]
edgelist1=[(1,2)]
edgelist2=[("a","b"),("b","c"),("a","d"),("d","e"),("e","b")]
edgelist3=[("a","b"),("b","c"),("c","a"),("c","d")]
G=Graph()
G.add_edges(edgelist2)

G.adjacency_matrix()
G.shortest_path("a")
print G.pagerank()



