<?xml version="1.0" encoding="utf-8"?>
<!DOCTYPE eagle SYSTEM "eagle.dtd">
<eagle version="9.3.1">
<drawing>
<settings>
<setting alwaysvectorfont="yes"/>
<setting verticaltext="up"/>
</settings>
<grid distance="0.1" unitdist="inch" unit="inch" style="lines" multiple="1" display="no" altdistance="0.01" altunitdist="inch" altunit="inch"/>
<layers>
<layer number="1" name="Top" color="4" fill="1" visible="no" active="no"/>
<layer number="16" name="Bottom" color="1" fill="1" visible="no" active="no"/>
<layer number="17" name="Pads" color="2" fill="1" visible="no" active="no"/>
<layer number="18" name="Vias" color="2" fill="1" visible="no" active="no"/>
<layer number="19" name="Unrouted" color="6" fill="1" visible="no" active="no"/>
<layer number="20" name="Dimension" color="15" fill="1" visible="no" active="no"/>
<layer number="21" name="tPlace" color="7" fill="1" visible="no" active="no"/>
<layer number="22" name="bPlace" color="7" fill="1" visible="no" active="no"/>
<layer number="23" name="tOrigins" color="15" fill="1" visible="no" active="no"/>
<layer number="24" name="bOrigins" color="15" fill="1" visible="no" active="no"/>
<layer number="25" name="tNames" color="7" fill="1" visible="no" active="no"/>
<layer number="26" name="bNames" color="7" fill="1" visible="no" active="no"/>
<layer number="27" name="tValues" color="7" fill="1" visible="no" active="no"/>
<layer number="28" name="bValues" color="7" fill="1" visible="no" active="no"/>
<layer number="29" name="tStop" color="7" fill="3" visible="no" active="no"/>
<layer number="30" name="bStop" color="7" fill="6" visible="no" active="no"/>
<layer number="31" name="tCream" color="7" fill="4" visible="no" active="no"/>
<layer number="32" name="bCream" color="7" fill="5" visible="no" active="no"/>
<layer number="33" name="tFinish" color="6" fill="3" visible="no" active="no"/>
<layer number="34" name="bFinish" color="6" fill="6" visible="no" active="no"/>
<layer number="35" name="tGlue" color="7" fill="4" visible="no" active="no"/>
<layer number="36" name="bGlue" color="7" fill="5" visible="no" active="no"/>
<layer number="37" name="tTest" color="7" fill="1" visible="no" active="no"/>
<layer number="38" name="bTest" color="7" fill="1" visible="no" active="no"/>
<layer number="39" name="tKeepout" color="4" fill="11" visible="no" active="no"/>
<layer number="40" name="bKeepout" color="1" fill="11" visible="no" active="no"/>
<layer number="41" name="tRestrict" color="4" fill="10" visible="no" active="no"/>
<layer number="42" name="bRestrict" color="1" fill="10" visible="no" active="no"/>
<layer number="43" name="vRestrict" color="2" fill="10" visible="no" active="no"/>
<layer number="44" name="Drills" color="7" fill="1" visible="no" active="no"/>
<layer number="45" name="Holes" color="7" fill="1" visible="no" active="no"/>
<layer number="46" name="Milling" color="3" fill="1" visible="no" active="no"/>
<layer number="47" name="Measures" color="7" fill="1" visible="no" active="no"/>
<layer number="48" name="Document" color="7" fill="1" visible="no" active="no"/>
<layer number="49" name="Reference" color="7" fill="1" visible="no" active="no"/>
<layer number="51" name="tDocu" color="7" fill="1" visible="no" active="no"/>
<layer number="52" name="bDocu" color="7" fill="1" visible="no" active="no"/>
<layer number="88" name="SimResults" color="9" fill="1" visible="no" active="yes"/>
<layer number="89" name="SimProbes" color="9" fill="1" visible="yes" active="yes"/>
<layer number="90" name="Modules" color="5" fill="1" visible="yes" active="yes"/>
<layer number="91" name="Nets" color="2" fill="1" visible="yes" active="yes"/>
<layer number="92" name="Busses" color="1" fill="1" visible="yes" active="yes"/>
<layer number="93" name="Pins" color="2" fill="1" visible="no" active="yes"/>
<layer number="94" name="Symbols" color="4" fill="1" visible="yes" active="yes"/>
<layer number="95" name="Names" color="7" fill="1" visible="yes" active="yes"/>
<layer number="96" name="Values" color="7" fill="1" visible="yes" active="yes"/>
<layer number="97" name="Info" color="7" fill="1" visible="yes" active="yes"/>
<layer number="98" name="Guide" color="6" fill="1" visible="yes" active="yes"/>
<layer number="99" name="SpiceOrder" color="7" fill="1" visible="yes" active="yes"/>
</layers>
<schematic xreflabel="%F%N/%S.%C%R" xrefpart="/%S.%C%R">
<libraries>
<library name="ngspice-simulation" urn="urn:adsk.eagle:library:527439">
<description>SPICE compatible library parts</description>
<packages>
</packages>
<symbols>
<symbol name="VOLTAGE" urn="urn:adsk.eagle:symbol:527440/5" library_version="18">
<description>Independent Voltage Source, either DC, AC, PULSE, SINE, PWL, EXP, or SFFM</description>
<circle x="0" y="0" radius="5.08" width="0.1524" layer="94"/>
<pin name="+" x="0" y="7.62" visible="off" length="short" direction="pas" rot="R270"/>
<pin name="-" x="0" y="-7.62" visible="off" length="short" direction="pas" rot="R90"/>
<text x="7.62" y="2.54" size="1.778" layer="95">&gt;NAME</text>
<text x="7.62" y="0" size="1.778" layer="96">&gt;VALUE</text>
<text x="7.62" y="-2.54" size="1.778" layer="97">&gt;SPICEMODEL</text>
<text x="7.62" y="-5.08" size="1.778" layer="97">&gt;SPICEEXTRA</text>
<wire x1="-1.27" y1="2.54" x2="1.27" y2="2.54" width="0.1524" layer="94"/>
<wire x1="0" y1="3.81" x2="0" y2="1.27" width="0.1524" layer="94"/>
<wire x1="-1.27" y1="-2.54" x2="1.27" y2="-2.54" width="0.1524" layer="94"/>
</symbol>
<symbol name="0" urn="urn:adsk.eagle:symbol:527455/1" library_version="18">
<description>Simulation ground symbol (spice node 0)</description>
<wire x1="-2.54" y1="0" x2="2.54" y2="0" width="0.1524" layer="94"/>
<wire x1="2.54" y1="0" x2="0" y2="-2.54" width="0.1524" layer="94"/>
<wire x1="0" y1="-2.54" x2="-2.54" y2="0" width="0.1524" layer="94"/>
<pin name="0" x="0" y="0" visible="off" length="point" direction="sup"/>
</symbol>
<symbol name="R" urn="urn:adsk.eagle:symbol:527454/4" library_version="18">
<description>RESISTOR</description>
<wire x1="-2.54" y1="-0.889" x2="2.54" y2="-0.889" width="0.254" layer="94"/>
<wire x1="2.54" y1="0.889" x2="-2.54" y2="0.889" width="0.254" layer="94"/>
<wire x1="2.54" y1="-0.889" x2="2.54" y2="0.889" width="0.254" layer="94"/>
<wire x1="-2.54" y1="-0.889" x2="-2.54" y2="0.889" width="0.254" layer="94"/>
<pin name="1" x="-5.08" y="0" visible="off" length="short" direction="pas" swaplevel="1"/>
<pin name="2" x="5.08" y="0" visible="off" length="short" direction="pas" swaplevel="1" rot="R180"/>
<text x="-2.54" y="2.54" size="1.778" layer="95">&gt;NAME</text>
<text x="-2.54" y="-6.35" size="1.778" layer="97">&gt;SPICEMODEL</text>
<text x="-2.54" y="-3.81" size="1.778" layer="96">&gt;VALUE</text>
<text x="-2.54" y="-8.89" size="1.778" layer="97">&gt;SPICEEXTRA</text>
</symbol>
</symbols>
<devicesets>
<deviceset name="VOLTAGE" urn="urn:adsk.eagle:component:527469/5" prefix="V" uservalue="yes" library_version="18">
<description>Independent Voltage Source, either DC, AC, PULSE, SINE, PWL, EXP, or SFFM</description>
<gates>
<gate name="G$1" symbol="VOLTAGE" x="0" y="0"/>
</gates>
<devices>
<device name="">
<technologies>
<technology name="">
<attribute name="VALUE" value="0V" constant="no"/>
<attribute name="_EXTERNAL_" value="" constant="no"/>
</technology>
</technologies>
</device>
</devices>
<spice>
<pinmapping spiceprefix="V">
<pinmap gate="G$1" pin="+" pinorder="1"/>
<pinmap gate="G$1" pin="-" pinorder="2"/>
</pinmapping>
</spice>
</deviceset>
<deviceset name="GND" urn="urn:adsk.eagle:component:527478/1" prefix="X_" library_version="18">
<description>Simulation ground symbol (spice node 0)</description>
<gates>
<gate name="G$1" symbol="0" x="0" y="0"/>
</gates>
<devices>
<device name="">
<technologies>
<technology name="">
<attribute name="SPICEGROUND" value=""/>
<attribute name="_EXTERNAL_" value=""/>
</technology>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="R" urn="urn:adsk.eagle:component:527474/6" prefix="R" uservalue="yes" library_version="18">
<description>RESISTOR</description>
<gates>
<gate name="G$1" symbol="R" x="0" y="0"/>
</gates>
<devices>
<device name="">
<technologies>
<technology name="">
<attribute name="_EXTERNAL_" value="" constant="no"/>
</technology>
</technologies>
</device>
</devices>
<spice>
<pinmapping spiceprefix="R">
<pinmap gate="G$1" pin="1" pinorder="1"/>
<pinmap gate="G$1" pin="2" pinorder="2"/>
</pinmapping>
</spice>
</deviceset>
</devicesets>
</library>
</libraries>
<attributes>
</attributes>
<variantdefs>
</variantdefs>
<classes>
<class number="0" name="default" width="0" drill="0">
</class>
</classes>
<parts>
<part name="V1" library="ngspice-simulation" library_urn="urn:adsk.eagle:library:527439" deviceset="VOLTAGE" device="" value="DC 2.8 AC 0"/>
<part name="X_1" library="ngspice-simulation" library_urn="urn:adsk.eagle:library:527439" deviceset="GND" device=""/>
<part name="X_2" library="ngspice-simulation" library_urn="urn:adsk.eagle:library:527439" deviceset="GND" device=""/>
<part name="R1" library="ngspice-simulation" library_urn="urn:adsk.eagle:library:527439" deviceset="R" device="" value="10000"/>
<part name="R2" library="ngspice-simulation" library_urn="urn:adsk.eagle:library:527439" deviceset="R" device="" value="1000"/>
<part name="R3" library="ngspice-simulation" library_urn="urn:adsk.eagle:library:527439" deviceset="R" device="" value="0.1"/>
<part name="V2" library="ngspice-simulation" library_urn="urn:adsk.eagle:library:527439" deviceset="VOLTAGE" device="" value="DC 3.3 AC 0"/>
<part name="RL" library="ngspice-simulation" library_urn="urn:adsk.eagle:library:527439" deviceset="R" device="" value="1"/>
</parts>
<sheets>
<sheet>
<plain>
</plain>
<instances>
<instance part="V1" gate="G$1" x="20.32" y="66.04" smashed="yes" rot="MR0">
<attribute name="NAME" x="12.7" y="68.58" size="1.778" layer="95" rot="MR0"/>
<attribute name="VALUE" x="12.7" y="66.04" size="1.778" layer="96" rot="MR0"/>
</instance>
<instance part="X_1" gate="G$1" x="63.5" y="38.1" smashed="yes"/>
<instance part="X_2" gate="G$1" x="20.32" y="53.34" smashed="yes"/>
<instance part="R1" gate="G$1" x="40.64" y="71.12" smashed="yes" rot="R270">
<attribute name="NAME" x="43.18" y="73.66" size="1.778" layer="95" rot="R270"/>
<attribute name="VALUE" x="36.83" y="73.66" size="1.778" layer="96" rot="R270"/>
</instance>
<instance part="R2" gate="G$1" x="53.34" y="60.96" smashed="yes">
<attribute name="NAME" x="50.8" y="63.5" size="1.778" layer="95"/>
<attribute name="VALUE" x="50.8" y="57.15" size="1.778" layer="96"/>
</instance>
<instance part="R3" gate="G$1" x="63.5" y="53.34" smashed="yes" rot="R90">
<attribute name="NAME" x="60.96" y="50.8" size="1.778" layer="95" rot="R90"/>
<attribute name="VALUE" x="67.31" y="50.8" size="1.778" layer="96" rot="R90"/>
</instance>
<instance part="V2" gate="G$1" x="78.74" y="71.12" smashed="yes">
<attribute name="NAME" x="86.36" y="73.66" size="1.778" layer="95"/>
<attribute name="VALUE" x="86.36" y="71.12" size="1.778" layer="96"/>
</instance>
<instance part="RL" gate="G$1" x="63.5" y="71.12" smashed="yes" rot="MR270">
<attribute name="NAME" x="60.96" y="73.66" size="1.778" layer="95" rot="MR270"/>
<attribute name="VALUE" x="67.31" y="73.66" size="1.778" layer="96" rot="MR270"/>
</instance>
</instances>
<busses>
</busses>
<nets>
<net name="VDD" class="0">
<segment>
<pinref part="V1" gate="G$1" pin="+"/>
<wire x1="20.32" y1="73.66" x2="20.32" y2="76.2" width="0.1524" layer="91"/>
<wire x1="20.32" y1="76.2" x2="40.64" y2="76.2" width="0.1524" layer="91"/>
<pinref part="R1" gate="G$1" pin="1"/>
<label x="27.94" y="76.2" size="1.27" layer="95"/>
<probe x="38.1" y="81.28" size="1.27" layer="89" probetype="0"/>
</segment>
</net>
<net name="FB" class="0">
<segment>
<pinref part="R1" gate="G$1" pin="2"/>
<pinref part="R2" gate="G$1" pin="1"/>
<wire x1="40.64" y1="66.04" x2="40.64" y2="60.96" width="0.1524" layer="91"/>
<wire x1="40.64" y1="60.96" x2="48.26" y2="60.96" width="0.1524" layer="91"/>
<label x="43.18" y="60.96" size="1.27" layer="95"/>
<probe x="38.1" y="55.88" size="1.27" layer="89" rot="R180" probetype="0"/>
</segment>
</net>
<net name="LEDK" class="0">
<segment>
<pinref part="R2" gate="G$1" pin="2"/>
<wire x1="58.42" y1="60.96" x2="63.5" y2="60.96" width="0.1524" layer="91"/>
<pinref part="R3" gate="G$1" pin="2"/>
<wire x1="63.5" y1="60.96" x2="63.5" y2="58.42" width="0.1524" layer="91"/>
<pinref part="RL" gate="G$1" pin="2"/>
<wire x1="63.5" y1="60.96" x2="63.5" y2="66.04" width="0.1524" layer="91"/>
<junction x="63.5" y="60.96"/>
<label x="66.04" y="63.5" size="1.27" layer="95" rot="R270"/>
<probe x="68.58" y="63.5" size="1.27" layer="89" probetype="0"/>
</segment>
</net>
<net name="LEDA" class="0">
<segment>
<pinref part="RL" gate="G$1" pin="1"/>
<wire x1="63.5" y1="76.2" x2="63.5" y2="81.28" width="0.1524" layer="91"/>
<pinref part="V2" gate="G$1" pin="+"/>
<wire x1="63.5" y1="81.28" x2="78.74" y2="81.28" width="0.1524" layer="91"/>
<wire x1="78.74" y1="81.28" x2="78.74" y2="78.74" width="0.1524" layer="91"/>
<label x="66.04" y="83.82" size="1.27" layer="95"/>
<probe x="53.34" y="83.82" size="1.27" layer="89" probetype="0"/>
</segment>
</net>
<net name="0" class="0">
<segment>
<pinref part="X_1" gate="G$1" pin="0"/>
<pinref part="R3" gate="G$1" pin="1"/>
<wire x1="63.5" y1="38.1" x2="63.5" y2="43.18" width="0.1524" layer="91"/>
<pinref part="V2" gate="G$1" pin="-"/>
<wire x1="63.5" y1="43.18" x2="63.5" y2="48.26" width="0.1524" layer="91"/>
<wire x1="63.5" y1="43.18" x2="78.74" y2="43.18" width="0.1524" layer="91"/>
<wire x1="78.74" y1="43.18" x2="78.74" y2="63.5" width="0.1524" layer="91"/>
<junction x="63.5" y="43.18"/>
<label x="71.12" y="43.18" size="1.27" layer="95"/>
</segment>
<segment>
<pinref part="X_2" gate="G$1" pin="0"/>
<pinref part="V1" gate="G$1" pin="-"/>
<wire x1="20.32" y1="53.34" x2="20.32" y2="58.42" width="0.1524" layer="91"/>
<label x="20.32" y="55.88" size="1.27" layer="95" rot="R90"/>
</segment>
</net>
</nets>
</sheet>
</sheets>
</schematic>
</drawing>
<compatibility>
<note version="8.2" severity="warning">
Since Version 8.2, EAGLE supports online libraries. The ids
of those online libraries will not be understood (or retained)
with this version.
</note>
<note version="8.3" severity="warning">
Since Version 8.3, EAGLE supports URNs for individual library
assets (packages, symbols, and devices). The URNs of those assets
will not be understood (or retained) with this version.
</note>
<note version="8.4" severity="warning">
Since Version 8.4, EAGLE supports properties for SPICE simulation. 
Probes in schematics and SPICE mapping objects found in parts and library devices
will not be understood with this version. Update EAGLE to the latest version
for full support of SPICE simulation. 
</note>
</compatibility>
</eagle>
