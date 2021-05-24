rm output.o
cd build
cmake .. -DTARGET_GROUP=prod
make
cd main
mv main output.o
cp output.o ../..