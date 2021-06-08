import torch
import torch.nn.functional as F
import torchvision.transforms as T
from model import BestModel
from torch.utils.data import DataLoader
from dataset import MnistDataset

def train(model,optimizer,train_datalder,epochs,device):
    model.train()
    for epoch_id in range (epochs):
        for imgs, lbls in train_datalder:      # getting data
            imgs=imgs.to(device)
            lbls=lbls.to(device)
            optimizer.zero_grad()       # clearing calculated gradients from previous iteration
            predict=model(imgs)
            loss=F.nll_loss(predict,lbls)   # Loss calculation with gradient
            loss.backward()
            optimizer.step()       # updates parameters
            print(loss.item())
            

def main():
    use_cuda=False
    device=torch.device('cuda' if use_cuda else 'cpu')   #device config here
    epochs=5
    torch.manual_seed(256)
    transforms=T.Compose([ # Tensor Transformations
        T.ToTensor(),
        T.Normalize((0.5,),(0.5,)),
    ])
    train_datst=MnistDataset('data','train',transforms) # Dataset
    train_datalder=DataLoader(train_datst,batch_size=64,shuffle=True,num_workers=4) # Setup Dataloader
    model=BestModel()
    model=model.to(device)
    optimizer=torch.optim.Adam(model.parameters())     # Optimizer, for now default values
    train(model,optimizer,train_datalder,epochs,device)

if __name__=='__main__':
    main()