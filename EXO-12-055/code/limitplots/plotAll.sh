#!/bin/bash

root -l -q -b  buildPlotVector.C
root -l -q -b  buildPlotScalar.C
root -l -q -b  buildPlotPseudoScalar.C
root -l -q -b  buildPlotAxial.C
              
root -l -q -b  buildPlotVector_DD.C
root -l -q -b  buildPlotScalar_DD.C
root -l -q -b  buildPlotPseudoScalar_DD.C
root -l -q -b  buildPlotAxial_DD.C
