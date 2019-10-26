# Babymonitor: 


* the logiccontroller prints the data
* the temperature and light sensor can have different logic about sampling frequency and thresholds. One can also add different machine learning logic to them. 
Like only classify when above a particular threshold. Like it is currently in the file.
* in order to run code:

```
bash compile.sh

bash write_data.sh

bash write.sh

streamlit run plotter2.py
```

* Different classifiers can be used in each stream.
* Each classifier can respond to its own changes as can be seen in the demo (Also can be showed through tockloader listen)
