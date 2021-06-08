import torch
import torch.nn as nn
import torchvision.transforms as T
import torch.nn.functional as F
from torch.utils.data import DataLoader
from dataset import MnistDataset
class BestModel(nn.Module):
    def __init__(self):
        super(BestModel,self).__init__()
        self.fclay1=nn.Linear(3*40*40,512)    # Fully connected layer
        self.fclay2=nn.Linear(512,10)        #Another Layer
        #self.fclay3=nn.Linear(64,10)
    def forward(self, x):                 # Model operations here
        # print(x.size()) returns [64,3,40,40]
        x=x.view(x.size(0),-1)         # Flattening the shape of a tensor by view()
        
        #print(x.size())        # returns [64,4800] flattened after view()        
        x=self.fclay1(x)
        
        #print(x.size())  # returns [64,128]        
        x=F.relu(x)     # Rectified linear function before another layer
        x=self.fclay2(x)
        # x=F.relu(x)
        # x=self.fclay3(x)
        x=torch.log_softmax(x,dim=1)  # softmax(sum of row =1.0 exactly) on the 2nd(dim=1) dimension: no of classes(size=10) and log for prevent infinity on small values
        return x

if __name__ == '__main__':
    transforms=T.Compose([ # Tensor Transformations
        T.ToTensor(),
        T.Normalize((0.5,),(0.5,)),
    ])
    datst=MnistDataset('data','train',transforms) # Dataset
    datalder=DataLoader(datst,batch_size=64,shuffle=True,num_workers=4) # Setup Dataloader
    model=BestModel()
    for imgs,lbls in datalder:
        predict=model(imgs) # Prediction(Output actually)
        # print(predict)
        exit()