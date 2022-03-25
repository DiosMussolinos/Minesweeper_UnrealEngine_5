// Fill out your copyright notice in the Description page of Project Settings.


#include "evoTest.h"

TArray<int> UevoTest::EvoTestValue(TArray<int> notes, int value)
{
    
    for (int i = 0; i < notes.Num(); i++)
    {
        for (int j = 0; j < notes.Num(); j++) 
        {
            int temp;

            if (notes[i] > notes[j])
            {
                temp = notes[i];

                notes[i] = notes[j];
                notes[j] = temp;
            }
        }
    }
    
    

    TArray<int> returnValue;

    int divisiveNum = 0;

    for (int i = 0; i < notes.Num(); i++)
    {
        if (value >= notes[i])
        {

            //divide values by notes[value]
            divisiveNum = value / notes[i];
            //Gets the remaining of the division
            int remaining = value % notes[i];

            //Update value for the remaining of division
            for (int j = divisiveNum; j > 0; j--)
            {
                //Add the notes X amount of times into the TArray
                returnValue.Add(notes[i]);
                divisiveNum--;
            }

            value = remaining;
        }
    }
    return returnValue;
}