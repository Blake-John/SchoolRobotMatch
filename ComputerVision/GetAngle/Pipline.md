# Get the Angle to Aim the Target

## 1. find the target

We will transform the `AutoAimming` module into a lib to get the targets and their position informations.

But before we apply the module to this project, we will first attempt the function **detecting the single target and calculate the angle** .

## 2. get the distance

If we want to get the angle, we must know how far does the target away from the camera. So we will also transform the `GetDistance` module into a lib.

## 3. get the angle

We will write a new module to get the angle **based on the position informations and the distance** 

# Pipline

1. transfrom the module `AutoAimming` and `GetDistance` , integrate and seperate them into the small module
2. test it on the single target
3. write the module to get the angle
4. apply all the module **on the img**
5. detect **webcam on real time**