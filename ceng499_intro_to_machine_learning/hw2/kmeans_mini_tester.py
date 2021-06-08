import numpy as np
from kmeans import forgy_initialize, initialize_cluster_centers, assign_clusters, calculate_cluster_centers, kmeans
import matplotlib.pyplot as mplt

def plot_clusters(data,k):
    centerlist=[]
    for i in range(10): # restarting 10 times
        initial_centers=initialize_cluster_centers(data,k)
        centers,objs=kmeans(data,initial_centers)
        print('center ',i,':',centers)
        centerlist.append(centers)
    mplt.scatter(data[:,0], data[:,1], c=assign_clusters(data,centerlist[-1]), s=5, cmap='viridis')
    mplt.scatter(centers[:,0], centers[:,1], marker='*', c='black', s=200)
    mplt.show()
def plotter(data): # elbow method plotter
    objective_vals=[]
    for k in range(1,11):
        obj_restarted_vals=[]
        for i in range(10): # restart
            initial_centers=initialize_cluster_centers(data,k)
            centers,objs=kmeans(data,initial_centers)
            obj_restarted_vals.append(objs)
            # print('restart davam edir')
        # print('restartlar bitdi',k)
        objective_vals.append(min(obj_restarted_vals))
    mplt.plot(range(1,11), objective_vals)
    mplt.xticks(range(1,11))
    mplt.xlabel("k values")
    mplt.ylabel("Objective Function-Best Final Values")
    mplt.show()


def main():
    cluster1=np.load('hw2_data/kmeans/clustering1.npy')
    cluster2=np.load('hw2_data/kmeans/clustering2.npy')
    cluster3=np.load('hw2_data/kmeans/clustering3.npy')
    cluster4=np.load('hw2_data/kmeans/clustering4.npy')
    print('Cluster1 entered:')
    plotter(cluster1)
    print('Cluster2 entered:')
    plotter(cluster2)
    print('Cluster3 entered:')
    plotter(cluster3)
    print('Cluster4 entered:')
    plotter(cluster4)
    plot_clusters(cluster1,2) # k=2 from elbow method
    plot_clusters(cluster2,3) # k=3 from elbow method
    plot_clusters(cluster3,4) # k=4 from elbow method
    plot_clusters(cluster4,5) # k=5 from elbow method




if __name__ == "__main__":
    main()


# The test data
# data = np.asarray([
#     [0.10819829, 0.62605985],
#     [2.51398245, -1.83387368],
#     [-1.10033618, 1.6260801],
#     [1.55090893, 0.50721597],
#     [0.06768307, 0.25987913],
#     [-0.71007112, -0.39629082],
#     [-0.15968428, 0.20188463],
#     [0.47420528, 0.15619532],
#     [0.32459835, -1.46679356],
#     [0.09095787, -1.28954287],
#     [0.79781624, 0.20330339],
#     [0.99588945, -0.51400183],
#     [0.55095553, 0.10900426],
#     [1.73990583, 2.31362988],
#     [0.90012845, 0.88261231],
#     [1.1065648, 2.19725047],
#     [0.47113742, 0.21261273],
#     [0.58259772, 2.02162784],
#     [1.82886198, 0.8951408],
#     [1.33025881, 1.16445873]
# ])

# initial_cluster_centers = np.asarray([
#     [0.37782442, 0.69733297],
#     [1.92131603, 2.96226556],
#     [1.51446483, 1.70932797]
# ])

# # Expected results
# assignments_gt = np.asarray([0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 2, 0, 2, 2, 2])
# new_cluster_centers_gt = np.asarray([
#     [0.45842465, -0.04771034],
#     [1.92131603, 2.96226556],
#     [1.31763783, 1.71842154]
# ])
# resultant_cluster_centers_gt = np.asarray([
#     [0.4924973, -0.39614757],
#     [1.14302278, 2.17750273],
#     [0.76967005, 0.95026129]
# ])
# obj_function_gt = 20.30670902775301

# # Tests
# # print('forgy',forgy_initialize(data,3))
# # init=initialize_cluster_centers(data,3)
# # print('initialized',init)
# assignments = assign_clusters(data, initial_cluster_centers)
# print('assign_clusters test:', np.all(assignments == assignments_gt))

# new_cluster_centers = calculate_cluster_centers(data, assignments, initial_cluster_centers, 3)
# print('calculate_cluster_centers test:', np.all(np.abs(new_cluster_centers - new_cluster_centers_gt) < 10 ** -5))
# # print('asdas',initialize_cluster_centers(data,3))
# resultant_cluster_centers, obj_function = kmeans(data, initial_cluster_centers)
# print('kmeans test (resultant_cluster_centers):',
#        np.all(np.abs(resultant_cluster_centers - resultant_cluster_centers_gt) < 10 ** -5))
# print('kmeans test (obj_function):', abs(obj_function - obj_function_gt) < 10 ** -5)
