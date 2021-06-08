import numpy as np
def calculate_distances(train_data, test_datum):
    """
    Calculates euclidean distances between test_datum and every train_data
    :param train_data: An (N, D) shaped numpy array where N is the number of examples
    and D is the dimension of the data
    :param test_datum: A (D, ) shaped numpy array
    :return: An (N, ) shaped numpy array that contains distances
    """
    distlist=[]
    s=np.shape(train_data)[0]
    for i in range(s):
        distance=np.linalg.norm(train_data[i]-test_datum)
        distlist.append(distance)
    distlistasnp=np.asarray(distlist)
    return distlistasnp



def majority_voting(distances, labels, k):
    """
    Applies majority voting. If there are more then one major class, returns the smallest label.
    :param distances: An (N, ) shaped numpy array that contains distances
    :param labels: An (N, ) shaped numpy array that contains labels
    :param k: An integer. The number of nearest neighbor to be selected.
    :return: An integer. The label of the majority class.
    """
    maxlabelvalue=np.max(labels)

    idxs=np.argpartition(distances,k) # returns list of indexes of smallest values at beginning
    liste=[0]*(maxlabelvalue+1) # list initiated with 0
    for j in range(k):
        liste[labels[idxs[j]]]+=1
    
    return liste.index(max(liste)) # returns first index of the max value
    

    


def knn(train_data, train_labels, test_data, test_labels, k):
    """
    Calculates accuracy of knn on test data using train_data.
    :param train_data: An (N, D) shaped numpy array where N is the number of examples
    and D is the dimension of the data
    :param train_labels: An (N, ) shaped numpy array that contains labels
    :param test_data: An (M, D) shaped numpy array where M is the number of examples
    and D is the dimension of the data
    :param test_labels: An (M, ) shaped numpy array that contains labels
    :param k: An integer. The number of nearest neighbor to be selected.
    :return: A float. The calculated accuracy.
    """
    sum=0
    s=np.shape(test_data)[0]
    for i in range(s):
        if(majority_voting(calculate_distances(train_data,test_data[i]),train_labels,k)==test_labels[i]):
            sum+=1
    return sum/s


def split_train_and_validation(whole_train_data, whole_train_labels, validation_index, k_fold):
    """
    Splits training dataset into k and returns the validation_indexth one as the
    validation set and others as the training set. You can assume k_fold divides N.
    :param whole_train_data: An (N, D) shaped numpy array where N is the number of examples
    and D is the dimension of the data
    :param whole_train_labels: An (N, ) shaped numpy array that contains labels
    :param validation_index: An integer. 0 <= validation_index < k_fold. Specifies which fold
    will be assigned as validation set.
    :param k_fold: The number of groups that the whole_train_data will be divided into.
    :return: train_data, train_labels, validation_data, validation_labels
    train_data.shape is (N-N/k_fold, D).
    train_labels.shape is (N-N/k_fold, ).
    validation_data.shape is (N/k_fold, D).
    validation_labels.shape is (N/k_fold, ).
    """
    n=np.shape(whole_train_data)[0]
    d=np.shape(whole_train_data)[1]
    splitted_train_data=np.array_split(whole_train_data,k_fold)
    splitted_train_label=np.array_split(whole_train_labels,k_fold)
    validation_data=splitted_train_data[validation_index]
    validation_label=splitted_train_label[validation_index]
    splitted_train_data_2=np.delete(splitted_train_data,validation_index,axis=0)
    splitted_train_label_2=np.delete(splitted_train_label,validation_index,axis=0)
    train_data=splitted_train_data_2.reshape(n-int(n/k_fold),d)
    train_labels=splitted_train_label_2.reshape(-1)
    return train_data,train_labels,validation_data,validation_label



def cross_validation(whole_train_data, whole_train_labels, k, k_fold):
    """
    Applies k_fold cross-validation and averages the calculated accuracies.
    :param whole_train_data: An (N, D) shaped numpy array where N is the number of examples
    and D is the dimension of the data
    :param whole_train_labels: An (N, ) shaped numpy array that contains labels
    :param k: An integer. The number of nearest neighbor to be selected.
    :param k_fold: An integer.
    :return: A float. Average accuracy calculated.
    """
    avacc=0
    for i in range(k_fold):
        p,q,r,s=split_train_and_validation(whole_train_data,whole_train_labels,i,k_fold)
        avacc+=knn(p,q,r,s,k)
    return avacc/k_fold