import numpy as np
import matplotlib.pyplot as plt
import pandas as pd
from scipy import stats

rng=np.random.default_rng(42)

M=10000

distributions={
    "Normal":stats.norm(loc=5,scale=1),
    "Beta":stats.beta(a=0.5,b=0.5),
    "Chi-square":stats.chi2(df=5)
}
sample_sizes=[2,5,10,20,50,100]
confidence_levels=[0.95,0.99]

def estimate_coverage(distribution,N,confidence,rng,M=100):
    true_mean=distribution.mean()

    success_count=0

    for i in range(M):
        samples=distribution.rvs(size=N,random_state=rng)

        sample_mean=np.mean(samples)
        se=stats.sem(samples)
        lower,upper=stats.t.interval(
            confidence=confidence,
            df=N-1,
            loc=sample_mean,
            scale=se
        )

        if lower<=true_mean<=upper:
            success_count+=1

    coverage=success_count/M
    return coverage

records=[]

for name,distribution in distributions.item():
    for n in sample_sizes:
        for confidence in confidence_levels:
            coverage=estimate_coverage(
                distribution=distribution,
                N=n,
                confidence=confidence,
                rng=rng,
                M=M
            )

            records.append(
                {
                    "Distribution":name,
                    "N":n,
                    "Confidence":confidence,
                    "Coverage":coverage,
                }
            )
df=pd.DataFrame(records)

df["Coverage(%)"]=df["Coverage"]*100

print(df.to_string(index=False))
