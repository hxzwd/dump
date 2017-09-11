package main

import (
	"fmt"
	"math/rand"
	"regexp"
	"strings"
	//	"github.com/gonum/blas/blas64"
	//	"github.com/gonum/matrix"
	"github.com/gonum/matrix/mat64"
)

func MaxInts(x int, y int) int {
	if x >= y {
		return x
	} else {
		return y
	}
}

func randomMatrix(n int, m int) *mat64.Dense {
	data := make([]float64, n*m)
	for i := range data {
		data[i] = rand.NormFloat64()
	}
	return mat64.NewDense(n, m, data)
}

func zeroMatrix(n int, m int) *mat64.Dense {
	data := make([]float64, n*m)
	for i := range data {
		data[i] = 0.0
	}
	return mat64.NewDense(n, m, data)
}

func diagonalMatrix(d []float64) *mat64.Dense {
	M := zeroMatrix(len(d), len(d))
	for i := 0; i < len(d); i++ {
		M.Set(i, i, d[i])
	}
	return M
}

func Matrix2String(M *mat64.Dense) string {
	return fmt.Sprintf("%v", mat64.Formatted(M))
}

func MatrixTranspose(M *mat64.Dense) *mat64.Dense {
	return mat64.DenseCopyOf(M.T())
}

func printMatrix(M *mat64.Dense, info string) {
	fmt.Printf("%s\n%s\n", info, Matrix2String(M))
}

func Matrix2Dense(M mat64.Matrix) *mat64.Dense {
	return mat64.DenseCopyOf(M)
}

func Dense2Matrix(M *mat64.Dense, Mat *mat64.Matrix) {
	MatDense := mat64.DenseCopyOf(*Mat)
	MatDense.SetRawMatrix(M.RawMatrix())
}

func FillMatrixZero(n int, m int) mat64.Dense {
	var R mat64.Dense
	R.SetRawMatrix(zeroMatrix(n, m).RawMatrix())
	return R
}

func AddMatrix(A mat64.Dense, B mat64.Dense) *mat64.Dense {
	n, m := A.Dims()
	C := mat64.NewDense(n, m, nil)
	C.Add(&A, &B)
	return C
}

func CompareMatrixDims(A *mat64.Dense, B *mat64.Dense) bool {
	nA, mA := A.Dims()
	nB, mB := B.Dims()
	if nA == nB && mA == mB {
		return true
	} else {
		return false
	}
}

func ReplaceAll(s string, src []string, dest []string) string {
	for i := range src {
		s = strings.Replace(s, src[i], dest[i], -1)
	}
	return s
}

func MaxInSlice(x []int) (int, int) {
	var MaxValue int
	var MaxValueIndex int
	MaxValue = 0
	for i := 0; i < len(x); i++ {
		if MaxValue < x[i] {
			MaxValue = x[i]
			MaxValueIndex = i
		} else {
			continue
		}
	}
	return MaxValue, MaxValueIndex
}

func MaxLenInList(StrList []string) (int, int) {
	Lens := make([]int, len(StrList), len(StrList))
	for i := 0; i < len(StrList); i++ {
		Lens[i] = len(StrList[i])
	}
	value, index := MaxInSlice(Lens)
	return value, index
}

func MaxLenInList2(StrList []string) int {
	value, _ := MaxLenInList(StrList)
	return value
}

func MaxLenInList3(StrList []string) int {
	tmp_pattern, _ := regexp.Compile(`[\-]{0,1}[\+]{0,1}[0-9]*[\.]{0,1}[0-9]*`)
	var Result int
	Result = 0
	for _, value := range StrList {
		TmpStringList := tmp_pattern.FindAllString(value, -1)
		CurrentMaxLen := MaxLenInList2(TmpStringList)
		if Result < CurrentMaxLen {
			Result = CurrentMaxLen
		}
	}
	return Result
}

func FillSlice(data []string, value string) []string {
	for i := range data {
		data[i] = value
	}
	return data
}

func FillSlice2(data []string, value string, begin int, end int) []string {
	if begin == end {
		return FillSlice(data, value)
	} else {
		for i := begin; i < end; i++ {
			data[i] = value
		}
		return data
	}
}

func getEmptyString(size int) string {
	EmptyString := ""
	for i := 0; i < size; i++ {
		EmptyString += " "
	}
	return EmptyString
}

func StrListElemsLens(list []string, max_len int) []string {
	var MaxLen int
	fmt.Println(len(list), list)
	for index, value := range list {
		list[index] = strings.Trim(value, " ")
		list[index] = ReplaceAll(list[index], []string{"\t", "\n", " "}, []string{"", "", " "})
	}
	if max_len <= 0 {
		MaxLen = MaxLenInList2(list)
	} else {
		MaxLen = max_len
	}
	fmt.Println("MaxLen ", MaxLen)
	for index, value := range list {
		if len(value) <= MaxLen {
			EmptyString := getEmptyString(MaxLen - len(value) + 1)
			fmt.Println("EmptyString len: ", len(EmptyString))
			list[index] = value + EmptyString
		}
	}
	return list
}

func SliceLens(x []string) ([]int, []int) {
	y := make([]int, len(x), len(x))
	z := make([]int, len(x), len(x))
	for index, value := range x {
		y[index] = len(value)
		z[index] = index
	}
	return y, z
}

func RemoveEmptyElements(x []string) []string {
	lens, _ := SliceLens(x)
	counter := 0
	for i := range lens {
		if lens[i] == 0 {
			continue
		} else {
			counter++
		}
	}
	result := make([]string, counter, counter)
	counter = 0
	for index, value := range x {
		if lens[index] == 0 {
			continue
		} else {
			result[counter] = value
			counter++
		}
	}
	return result
}

func CombineListElements(list []string) string {
	var result string
	result = ""
	for _, value := range list {
		result += value + " "
	}
	return result[:len(result)-1]
}

func addPositiveSign(x []string) []string {
	pattern, _ := regexp.Compile(`[\s]{1}[0-9]{1,}[\.]{1}[0-9]{1}`)
	var matches []string
	for index, value := range x {
		matches = pattern.FindAllString(value, -1)
		if len(matches) == 0 {
			continue
		}
		dest := make([]string, len(matches), len(matches))
		for i := 0; i < len(matches); i++ {
			dest[i] = "+" + matches[i][1:]
			matches[i] = matches[i][1:]
		}
		x[index] = ReplaceAll(value, matches, dest)
		fmt.Println("Dest: ", dest)
	}
	fmt.Println("Add pos: ", matches)

	return x
}

func TwoMat2String(A *mat64.Dense, B *mat64.Dense) string {
	var (
		ResultString       string
		nX, mX, nY, mY     int
		StrListX, StrListY []string
		Delimer            string
		s1, s2             string
		symb               string
		//		pos1, pos2         int
		//		old_pos1, old_pos2 int
	)
	//	pattern, _ := regexp.Compile(`([\s]{1}[0-9|\-]{1,}[\.]{0,1}[0-9]*[\s|^]{1}){1,}`)
	pattern, _ := regexp.Compile(`[\|]{1}[\s]*[^\n]+`)
	s1 = Matrix2String(A)
	s2 = Matrix2String(B)
	Source := []string{"⎤", "⎡", "⎦", "⎣", "⎢", "⎥"}
	Destination := []string{"|", "|", "|", "|", "|", "|"}
	s1 = ReplaceAll(s1, Source, Destination)
	s2 = ReplaceAll(s2, Source, Destination)
	symb = "\n"
	Delimer = "\t"
	ResultString = ""
	var counter int
	matched1 := pattern.FindAllString(s1, -1)
	matched2 := pattern.FindAllString(s2, -1)
	matched1 = addPositiveSign(matched1)
	matched2 = addPositiveSign(matched2)
	MaxStringLen := MaxInts(MaxLenInList2(matched1), MaxLenInList2(matched2))
	MaxNumberLen := MaxLenInList3(matched1)
	fmt.Println(matched1, "\n", matched2)
	for i, _ := range matched1 {
		TmpString := matched1[i]
		tmp_pattern, _ := regexp.Compile(`[\-]{0,1}[\+]{0,1}[0-9]*[\.]{0,1}[0-9]*`)
		//		TmpString := strings.Replace(matched1[i], "\n", "", -1)
		//		TmpString = strings.Replace(TmpString, "|", "", -1)
		//		TmpString = strings.Trim(TmpString, " ")
		//		TmpString = strings.Replace(TmpString, "  ", " ", -1)
		//		RowStringList := strings.Split(TmpString, " ")
		TmpStringList := tmp_pattern.FindAllString(TmpString, -1)
		RowStringList := RemoveEmptyElements(TmpStringList)
		fmt.Println("RowStringList ", RowStringList)
		fmt.Println("RowStringList len: ", len(RowStringList))
		TmpString = CombineListElements(StrListElemsLens(RowStringList, MaxNumberLen))
		//		TmpString = strings.Replace(TmpString, "+", " ", -1)
		fmt.Println("TmpString ", TmpString)
		matched1[i] = TmpString

		//		if CurrentLen < MaxStringLen {
		//			border_pos := strings.Index(matched1[i][1:], "|")
		//			fmt.Println(border_pos, CurrentLen, MaxStringLen)
		//			fmt.Println(matched1[i][0 : border_pos+1])
		//			fmt.Println(matched1[i][border_pos+1:])
		//			matched1[i] = matched1[i][0:border_pos+1] + getEmptyString(MaxStringLen-CurrentLen) + matched1[i][border_pos+1:]
		//			matched1[i] = TmpString + getEmptyString(MaxStringLen-CurrentLen)
		//		}
	}
	MaxStringLen = MaxInts(MaxLenInList2(matched1), MaxLenInList2(matched2))
	matched1 = StrListElemsLens(matched1, MaxStringLen)
	fmt.Println(matched1)
	//	for i := range matched2 {
	//		CurrentLen := len(matched2)
	//		if CurrentLen < MaxStringLen {
	//			border_pos := strings.Index(matched2[i][1:], "|")
	//			matched2[i] = matched2[i][0:border_pos] + getEmptyString(MaxStringLen-CurrentLen) + matched2[i][border_pos:]
	//		}
	//	}
	if CompareMatrixDims(A, B) {
		for index, value := range matched1 {
			ResultString += value + Delimer + matched2[index] + symb
		}
	} else {
		nA, mA := A.Dims()
		nB, mB := B.Dims()
		var X *mat64.Dense
		var Y *mat64.Dense
		if nA > nB {
			X = A
			Y = B
			nX = nA
			mX = mA
			nY = nB
			mY = mB
			StrListX = matched1
			StrListY = matched2
		} else {
			X = B
			Y = A
			nX = nB
			mX = mB
			nY = nA
			mY = mA
			StrListX = matched2
			StrListY = matched1
		}
		TmpStringList := make([]string, nX, nX)
		TmpStringList = FillSlice(TmpStringList, " ")
		copy(TmpStringList[0:nY], StrListY[:])
		StrListY = TmpStringList

		mX = mX
		mY = mY
		X = X
		Y = Y
		counter = counter
		for index, value := range StrListX {
			ResultString += value + Delimer + StrListY[index] + symb
		}
	}

	//	pos1 = 0
	//	pos2 = 0
	//	if CompareMatrixDims(A, B) {
	//		counter = 0
	//		n, _ := A.Dims()
	//		fmt.Printf("n is %d\n", n)
	//		for false {
	//			fmt.Printf("Counter: %d\n", counter)
	//			fmt.Printf("Res str is %s\n", ResultString)
	//			if counter == n {
	//				break
	//			}
	//			old_pos1 = pos1
	//			old_pos2 = pos2

	//			pos1 = strings.Index(s1[pos1+1:], symb) + old_pos1
	//			pos2 = strings.Index(s2[pos2+1:], symb) + old_pos2
	//			ResultString = ResultString + s1[old_pos1:pos1] +
	//				Delimer + s2[old_pos2:pos2] + "\n"
	//			fmt.Printf("Old pos is %d, %d\nPos is %d, %d\n", old_pos1, old_pos2, pos1, pos2)
	//			counter++
	//		}

	//	}
	return ResultString
}

var (
	mat2str = Matrix2String
	matT    = MatrixTranspose
	mat2den = Matrix2Dense
	den2mat = Dense2Matrix
)

func main() {
	fmt.Println("Fast golang tests\n")

	A := randomMatrix(3, 3)
	D := diagonalMatrix([]float64{-1.0, 0.0, 1.0})

	fmt.Printf("\nA\n%s\n", mat2str(A))

	fmt.Printf("\nZero matrix 2x2\n%s\n", mat2str(zeroMatrix(2, 2)))
	fmt.Printf("\nDiagonal matrix D by vector [-1, 0, 1]\n%s\n", mat2str(D))
	fmt.Printf("\nTransposed matrix D(D^T)\n%s\n", mat2str(matT(D)))
	printMatrix(matT(A), "\nA^T")

	var C mat64.Dense
	C.Mul(D, D)
	fmt.Printf("\nC = D*D\n%s\n", mat2str(&C))

	var B mat64.Dense
	B = FillMatrixZero(3, 3)
	printMatrix(&B, "\nZero matrix [3x3] B")

	B.Add(&C, D)
	printMatrix(&B, "\nB = D + C")
	D.Add(D, D)
	printMatrix(D, "\nD = D + D")
	printMatrix(AddMatrix(C, B), "\nC + B")

	//	fmt.Println(strings.Index("aksjdkj5sdjf", "6"))
	printMatrix(A, "")
	fmt.Printf("\n\n%s\n\n", TwoMat2String(A, matT(A)))

	Z := zeroMatrix(2, 4)
	printMatrix(Z, "\nZero matrix Z[2x4]")
	fmt.Printf("\n\n%s\n\n", TwoMat2String(A, Z))

	//	zero := mat64.NewDense(3, 4, nil)
	//	fmt.Println(zero)

	//	data := make([]float64, 36)

	//	for i := range data {
	//		data[i] = rand.NormFloat64()
	//	}
	//	a := mat64.NewDense(6, 6, data)
	//	tr := mat64.Trace(a)

	//	fmt.Printf("%v\n", mat64.Formatted(a))
	//	fmt.Printf("Tr(a) = %f", tr)

	//	zero.Copy(a)

	//	fmt.Printf("\na\n%v\n", mat64.Formatted(a))
	//	fmt.Printf("\nzero\n%v\n", mat64.Formatted(zero))

	//	var c mat64.Dense
	//	c.Mul(a, a)
	//	fmt.Printf("c = a*a\n%v\n", mat64.Formatted(c))
}
