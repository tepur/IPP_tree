#!/bin/bash

if [ $1 == "-v" ]
then
    for f in $3/*.in
    do
        ./$2 -v < $f > std_out.out 2> err_out.err
	if ! diff std_out.out ${f%in}out > diff_out1.out || ! diff err_out.err ${f%in}err > diff_out2.out
        then
            echo $f
        fi
    done
else
    for f in $2/*.in
    do
        ./$1 < $f > std_out.out
        if ! diff std_out.out ${f%in}out > diff_out.out
        then
            echo $f
        fi
    done
fi
