# Jack Text Meterbridge

This is an attempt use [stephanb2's](https://github.com/stephanb2/jack-meterbridge) maintenance version of [JACK Meterbridge](http://plugin.org.uk/meterbridge/) from Steve Harris (2002) to provide text based graphs that use VT100 codes for positioning.

Broadcast and Music Producers are advised to use [Ebumeter](http://kokkinizita.linuxaudio.org/linuxaudio/) by Fons Adriaensen, which offers loudness metering according to [EBU R-128](https://tech.ebu.ch/publications/r128). 

Check the [Awesome Broadcasting](https://github.com/ebu/awesome-broadcasting) list maintained by the EBU.

## Prerequisistes

Debian dependencies (aside from `build-essential`):
`libsdl-dev libsdl-image1.2-dev libjack-jackd2-dev`

TODO: `./configure` doesn't pick the dependency on `libsdl-image`

## Aims

* Bring PPM and VU ballistics in line with [Spifoski & Klar (2004) Levelling and Loudness. EBU technical Review - January 2004](https://tech.ebu.ch/docs/techreview/trev_297-spikofski_klar.pdf)
* Code cleanup
* Update Jack client ?

## License

This project is released under the GNU General Public License, version 3 (GPL-3.0)[https://opensource.org/licenses/GPL-3.0]

## Meters

### PPM - Peak Program level Meters

These meters are designed to indicate peak amplitude, as opposed to VU meters which are designed to indicate volume.

The scale is correct according to the standard, 4 equates to 0dB, 1 to -12, 7 to +12, and it is linear with decibels.

I've never used a real PPM meter, so I don't know if it reacts correctly. Feedback welcome.
	
### VU - Volume Unit meters

These meters are designed to measure the "volume" of an audio signal, it is not as relevant to digital systems as PPM meters, but is useful if you are interfacing to analogue tape, FM broadcast equipment or want a general idea of the signal volume.

The -r flag (set reference level) is useful with these meters as it will allow you to calibrate to your DA converters. The meter is pre-adjusted so that it should align correctly calibrated DA converters with analogue systems. If you wish to run with 0dBFS = 0dBu then use "-r 20"

### DPM - Digital Peak Meter

Conforming to IEC 268-18:1995 (peak indicator decay may not be correct).

These are meters as typically seen on digital consoles, HD recorders etc.

There are the most efficient in screen realestate and CPU use but look a bit boring ;)
