#!/bin/bash
thedataset=$1
# thedataset=`echo $thedataset | sed -e 's/[-]/HYPHEN/g'`
# thedataset=`echo $thedataset | sed -e 's/\//SLASH/g'`
# thedataset=`echo $thedataset | sed -e 's/\_/UNDERSCORE/g'`
ISGGH=$2
hadronType=$3
skim=$4
RUNERA=$5
DOCUTS=$6
njobs=$7
echo "thedataset is $thedataset"
echo "ISGGH is $ISGGH"
echo "hadronType is $hadronType"
echo "skim is $skim"
echo "RUNERA is $RUNERA"
echo "DOCUTS is $DOCUTS"
echo "njobs is $njobs"



cp Crab3Config_MC.py crab_template_temp.py
# sed -i "/$thedataset/s/^#//" crab_template_temp.py

thedataset=`echo $thedataset | sed -e 's/[-]/HYPHEN/g'`
thedataset=`echo $thedataset | sed -e 's/\//SLASH/g'`
thedataset=`echo $thedataset | sed -e 's/\_/UNDERSCORE/g'`
sed -ie "s/THEDATASET/$thedataset/g" crab_template_temp.py
sed -ie 's/HYPHEN/-/g' crab_template_temp.py
sed -ie 's/SLASH/\//g' crab_template_temp.py
sed -ie 's/UNDERSCORE/\_/g' crab_template_temp.py

sed -ie "s/NJOBS/$njobs/g" crab_template_temp.py
sed -ie "s/THESKIM/$skim/g" crab_template_temp.py
sed -ie "s/RUNERA/$RUNERA/g" crab_template_temp.py
sed -ie "s/THEHADRON/$hadronType/g" crab_template_temp.py


cp nTupliser_miniAOD_cfg.py theconfig.py
sed -ie "s/THESKIM/$skim/g" theconfig.py
sed -ie "s/DOCUTS/$DOCUTS/g" theconfig.py
sed -ie "s/ISGGH/$ISGGH/g" theconfig.py
sed -ie "s/THERUNERA/$RUNERA/g" theconfig.py
sed -ie "s/THEHADRON/$hadronType/g" theconfig.py

crab submit -c crab_template_temp.py
rm theconfig.py crab_template_temp*


