package main

import (
	"fmt"
	"math"
	"math/rand"
)


func sigm(x float64) float64 {
	return (1.0)/(1.0 + math.Exp(-x))
}

func dsigm(x float64) float64 {
	return sigm(x)*(1.0 - sigm(x))
}


func MatrixMul(M [4][3]float64, V [3]float64) []float64 {
	R := make([]float64, 4, 4)
	for i := 0; i < 4; i++ {
		R[i] = M[i][0]*V[0] + M[i][1]*V[1] + M[i][2]*V[2]
	}
	return R
}

func MatrixMul2(M [3][4]float64, V [4]float64) []float64 {
	R := make([]float64, 3, 3)
	for i := 0; i < 3; i++ {
		R[i] = M[i][0]*V[0] + M[i][1]*V[1] + M[i][2]*V[2] + M[i][3]*V[3]
	}
	return R
}

func MatrixTranspose(M [4][3]float64) [3][4]float64 {
	var R [3][4]float64
	for i := 0; i < 4; i++ {
		for j := 0; j < 3; j++ {
			R[j][i] = M[i][j]
		}
	}
	return R
}

func VecSigm(X []float64) []float64 {
	R := make([]float64, len(X), len(X))
	for index, value := range X {
		R[index] = sigm(value)
	}
	return R
}

func VecDsigm(X []float64) []float64 {
	R := make([]float64, len(X), len(X))
	for index, value := range X {
		R[index] = dsigm(value)
	}
	return R
}

func VecDiff(X []float64, Y []float64) []float64 {
	R := make([]float64, len(X), len(X))
	for index, value := range X {
		R[index] = value - Y[index]
	}
	return R
}

func VecEMul(X []float64, Y []float64) []float64 {
	R := make([]float64, len(X), len(X))
	for index, value := range X {
		R[index] = value * Y[index]
	}
	return R
}

func VecAdd(X []float64, Y []float64) []float64 {
	R := make([]float64, len(X), len(X))
	for index, value := range X {
		R[index] = value + Y[index]
	}
	return R
}

func MatrixAdd(X []float64, Y []float64) [3]float64 {
	var R [3]float64
	for index, value := range X {
		R[index] = value + Y[index]
	}
	return R
} 

func main() {
	fmt.Println("Multi-Layer perceptrone (MLP)\n")
	
	fmt.Println(sigm(0.0))
	fmt.Println(dsigm(0.0))
	
	var NumOfEpochs int	
	Inputs := [4][3]float64 {{0.0, 0.0, 1.0}, {0.0, 1.0, 1.0}, {1.0, 0.0, 1.0}, {1.0, 1.0, 1.0}}
	Outputs := [4]float64 {0.0, 0.0, 1.0, 1.0}
	Randomizer := rand.New(rand.NewSource(1))
	var Layer0 [4][3]float64
	var Layer0T [3][4]float64
	var Layer1 [4]float64

	W0 := [3]float64 {0.0, 0.0, 0.0}
	NumOfEpochs = 10000

	for index, _ := range W0 {
		W0[index] = 2.0*Randomizer.Float64() - 1.0
	}



	for counter := 0; counter < NumOfEpochs; counter++ {
		Layer0 = Inputs
		copy(Layer1[:], VecSigm(MatrixMul(Layer0, W0)))
		
		Layer1Errors := VecDiff(Outputs[:], Layer1[:])
		
		Layer1Delta := VecEMul(Layer1Errors, VecDsigm(Layer1[:]))

		Layer0T = MatrixTranspose(Layer0)
		var TmpArray [4]float64
		copy(TmpArray[:], Layer1Delta)
		W0 = MatrixAdd(W0[:], MatrixMul2(Layer0T, TmpArray))
	}		

/*
	fmt.Println(Layer0, Layer1)
	fmt.Println(Inputs, Outputs)
	fmt.Println(W0)
	fmt.Println(VecSigm(MatrixMul(Inputs, W0)))
	copy(Layer1[:], VecSigm(MatrixMul(Inputs, W0)))
	fmt.Println(Layer1)
*/
}
