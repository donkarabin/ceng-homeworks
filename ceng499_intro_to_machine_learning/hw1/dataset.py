import os
import torchvision.transforms as T
from torch.utils.data import Dataset,DataLoader
from PIL import Image

class MnistDataset(Dataset):
    def __init__ (self,dataset_path,split,transforms):
        ims_path=os.path.join(dataset_path,split) # Images folder path of train
        self.datalist=[]
        with open(os.path.join(ims_path,'labels.txt'),'r') as ff:
            for line in ff: 
                im_name,labl=line.split()
                im_path=os.path.join(ims_path,im_name) # Individual image path here
                labl=int(labl) # Integer Casting
                self.datalist.append((im_path, labl)) # append to the list as tuples
        self.transforms=transforms # Assigning transforms attribute
    def __len__ (self):
        return len(self.datalist)
    def __getitem__ (self,index):
        im_path=self.datalist[index][0] # Take individual image path
        labl=self.datalist[index][1]
        img= Image.open(im_path) # Opening image
        img=self.transforms(img) # Transforming image
        return img,labl

if __name__ == '__main__':
    transforms=T.Compose([  # Tensor Transformations
        T.ToTensor(),
        T.Normalize((0.5,),(0.5,)),
    ])
    datst=MnistDataset('data','train',transforms) # Dataset
    datalder=DataLoader(datst,batch_size=64,shuffle=True,num_workers=4) # Setup DataLoader
    for imgs,lbls in datalder:
        print(imgs.size())
        print(lbls)
        exit()