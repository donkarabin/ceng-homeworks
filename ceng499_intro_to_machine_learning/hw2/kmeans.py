import numpy as np
def forgy_initialize(data, k):  
    return data[np.random.choice(range(data.shape[0]),replace=False,size = k),:]

def initialize_cluster_centers(data, k):
    rand_x = np.random.uniform(np.min(data[:,0]),np.max(data[:,0]), k)
    rand_y = np.random.uniform(np.min(data[:,1]),np.max(data[:,1]), k)
    #print('shape of x',np.shape(rand_x),rand_x)
    a=np.reshape(rand_x,(k,1))
    b=np.reshape(rand_y,(k,1))
    # print('reshaped', np.shape(a),a)
    return np.concatenate((a,b),axis=1)

def assign_clusters(data, cluster_centers):
    """
    Assigns every data point to its closest (in terms of euclidean distance) cluster center.
    :param data: An (N, D) shaped numpy array where N is the number of examples
    and D is the dimension of the data
    :param cluster_centers: A (K, D) shaped numpy array where K is the number of clusters
    and D is the dimension of the data
    :return: An (N, ) shaped numpy array. At its index i, the index of the closest center
    resides to the ith data point.
    """
    resultlist=[]
    c=np.shape(cluster_centers)[0]
    d=np.shape(data)[0]
    templist=[0]*c
    for i in range(d):
        for j in range(c):
            distance=np.linalg.norm(cluster_centers[j]-data[i])
            templist[j]=distance
        minindex=templist.index(min(templist))
        resultlist.append(minindex)
    reslistasnp=np.asarray(resultlist)
    return reslistasnp
        



def calculate_cluster_centers(data, assignments, cluster_centers, k):
    """
    Calculates cluster_centers such that their squared euclidean distance to the data assigned to
    them will be lowest.
    If none of the data points belongs to some cluster center, then assign it to its previous value.
    :param data: An (N, D) shaped numpy array where N is the number of examples
    and D is the dimension of the data
    :param assignments: An (N, ) shaped numpy array with integers inside. They represent the cluster index
    every data assigned to.
    :param cluster_centers: A (K, D) shaped numpy array where K is the number of clusters
    and D is the dimension of the data
    :param k: Number of clusters
    :return: A (K, D) shaped numpy array that contains the newly calculated cluster centers.
    """
    c=np.shape(cluster_centers)[0]
    new_centers = np.zeros(cluster_centers.shape, dtype=cluster_centers.dtype)
    for i in range(c):
        clustarr= data[np.where(assignments==i)]
        if clustarr.size!=0:
            avgx=np.average(clustarr[:,0])
            avgy=np.average(clustarr[:,1])
            new_centers[i,0]=avgx
            new_centers[i,1]=avgy
        elif clustarr.size==0:
            new_centers[i]=cluster_centers[i]
    return new_centers




def kmeans(data, initial_cluster_centers):
    """
    Applies k-means algorithm.
    :param data: An (N, D) shaped numpy array where N is the number of examples
    and D is the dimension of the data
    :param initial_cluster_centers: A (K, D) shaped numpy array where K is the number of clusters
    and D is the dimension of the data
    :return: cluster_centers, objective_function
    cluster_center.shape is (K, D).
    objective function is a float. It is calculated by summing the squared euclidean distance between
    data points and their cluster centers.
    """
    centers=initial_cluster_centers
    k=np.shape(initial_cluster_centers)[0]
    diff=-8888
    while diff!=0:
        old_centers=centers
        assigned_clusters=assign_clusters(data,centers)
        centers= calculate_cluster_centers(data,assigned_clusters,centers,k)
        # print('abe',centers)
        diff = np.linalg.norm(centers-old_centers)
    c=np.shape(centers)[0]
    objective_value=0
    sum1=0
    for i in range(c):
        clustarr= data[np.where(assigned_clusters==i)]
        # print('clusterar',np.shape(clustarr))
        for j in range(np.shape(clustarr)[0]):
            sum1+=(np.linalg.norm(centers[i]-clustarr[j]))**2
        # print('sumumuz',sum1)
    objective_value=sum1
    # print('objfunncccccccc', objective_value)
    return centers,objective_value