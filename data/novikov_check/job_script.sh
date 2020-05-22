#!/bin/bash

#Submit this script with: sbatch thefilename

#SBATCH --time=15:00:00   # walltime
#SBATCH --ntasks=60   # number of processor cores (i.e. tasks)
#SBATCH -p defq   # partition(s)
#SBATCH -J "Novikov check"   # job name
#SBATCH --mail-user=egerlanc@physik.hu-berlin.de   # email address
#SBATCH --mail-type=BEGIN
#SBATCH --mail-type=END
#SBATCH --mail-type=FAIL

mpirun ./../../bin/suscept_mpi_new -f lif_c_1e-1.ini &&
mpirun ./../../bin/suscept_mpi_new -f lif_c_1e-2.ini &&
mpirun ./../../bin/suscept_mpi_new -f lif_c_5e-1.ini &&
mpirun ./../../bin/suscept_mpi_new -f lif_c_9e-1.ini &&
mpirun ./../../bin/suscept_mpi_new -f lif_c_1e0.ini
