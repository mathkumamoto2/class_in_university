import numpy as np
import matplotlib.pyplot as plt
from scipy import stats

M=10000
NS=[1,2,5,10,20,50]
dis=["normal","beta","chisquare"]

def mean_normal(N):
    mean_array=[]
    for i in range(M):
        mean_array.append(np.mean(np.random.normal(0,1,N)))
    return np.array(mean_array)

def mean_beta(N):
    mean_array=[]
    for i in range(M):
        mean_array.append(np.mean(np.random.beta(0.5,0.5,N)))

    return np.array(mean_array)
def mean_chisquare(N):
    mean_array=[]
    for i in range(M):
        mean_array.append(np.mean(np.random.chisquare(5,N)))
    return np.array(mean_array)
def plot_normal(NS):
    fig,ax=plt.subplots(1,len(NS),figsize=(30,4))
    for i ,N in enumerate(NS):
        sample_mean=mean_normal(N)

        x=np.linspace(sample_mean.min(),sample_mean.max(),300)
        y=stats.norm.pdf(x,loc=0,scale=1/np.sqrt(N))
        ax[i].hist(sample_mean,bins="auto",density=True,alpha=0.6,label="simulataion")
        ax[i].plot(x,y,label="normal thory")
        ax[i].set_title(f"Normal,N={N}")
        ax[i].set_xlabel("Sample mean")
        ax[i].set_ylabel("Density")
        ax[i].legend()
    plt.tight_layout()
    plt.show()

def plot_beta(NS):
    fig,ax=plt.subplots(1,len(NS),figsize=(30,4))
    beta_mean=0.5
    beta_var=0.125

    for i,N in enumerate(NS):
        sample_mean=mean_beta(N)
        x=np.linspace(sample_mean.min(),sample_mean.max(),300)
        y=stats.norm.pdf(x,loc=beta_mean,scale=np.sqrt(beta_var/N))
        ax[i].hist(sample_mean,bins="auto",density=True,alpha=0.6,label="simulation")
        ax[i].plot(x,y,label="normal approximation")
        ax[i].set_title(f"Beta(0.5,0.5),N={N}")
        ax[i].set_xlabel("Sample mean")
        ax[i].set_ylabel("Density")
        ax[i].legend()
    plt.tight_layout()
    plt.show()

def plot_chisquare(NS):
    fig,ax=plt.subplots(1,len(NS),figsize=(30,4))
    df=5
    chi_mean=df
    chi_var=2*df

    for i,N in enumerate(NS):
        sample_mean=mean_chisquare(N)

        x=np.linspace(sample_mean.min(),sample_mean.max())
        y=stats.norm.pdf(x,loc=chi_mean,scale=np.sqrt(chi_var/N))

        ax[i].hist(sample_mean,bins="auto",density=True,label="Simulation")
        ax[i].plot(x,y,label="normal approximation")
        ax[i].legend()

    plt.tight_layout()
    plt.show()
alpha=0.5
def mean_pareto(N):
    mean_array=[]
    for i in range(M):
        sample=stats.pareto.rvs(b=alpha,scale=0.1,size=N)
        mean_array.append(np.mean(sample))
    return np.array(mean_array)

def plot_pareto(NS):
    fig,ax=plt.subplots(1,len(NS),figsize=(30,4))
    x_max=np.percentile(sample_mean,99)
    x=np.linspace(1,x_max,300)

    for i,N in enumerate(NS):
        sample_mean=mean_pareto(NS)
        ax[i].hist(
            sample_mean,
            bins=50,
            range=(1,x_max),
            density=True,
            alpha=0.6,
            label="simulation"
        )
        pareto_mean=alpha/(alpha-1)
        ax[i].axvline(
            pareto_mean,
            color="red",
            linestyle="--",
            label="thioretical mean"
        )
        if N==1:
            y=stats.pareto.pdf(x,b=alpha,scale=1)/stats.pareto.cdf(x_max,b=alpha,scale=1)
            ax[i].plot(x,y,label="Pareto theory")
        ax[i].set_xlim(1,x_max)
        ax[i].set_title(f"Pareto,N={N}")
        ax[i].set_xlabel("Sample mean")
        ax[i].set_ylabel("Density")
        ax[i].legend()
    plt.tight_layout()
    plt.show()

for char in dis:
    if char=="normal":
        plot_normal(NS)
    elif char=="beta":
        plot_beta(NS)
    else:
        plot_chisquare(NS)


