Fast Fourier Transformation for Noise
=====================================

For the electronic noise investigation the data obtained with alpha
sorce placed on anode 7 is used. The anode which are far from this
one contain noise only signals.


It's also possible to deal with data obtained by generator 
pulses without beam is used.
Generator signal ioccured at around channel 2000, so everything
which came earlear, when channel 1800 can be considered as
pure noise of electronic chain.


Stability and correlation
-------------------------

It has beenchecked that base line for every anode channel is
stable within 5000 events run (20 Hz generator fequency).
The distribution of the baseline for each channel has 
close-to-gaussian shape.

No visible correlation was observed.

For more see **_MC4NOISE.docx_**.

Frequiency spectra
------------------

To dump spectrum for particular anede for loaded event into
**_dump.txt_** file there is a dedicated metod in the 
**tpcEvent** class. Dumped spectra should be analysed with
**anode_noise.py**.

