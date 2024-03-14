#include <khanh.h>

long structSize = 100;

struct Array {
  int size;
  long data[100];
};


void print(struct Array arr) {
  for (int i=0; i < arr.size; ++i) printf("%li ", arr.data[i]);
  printf("(%d) \n", arr.size);
};

void addStructArray(struct Array* arr1, struct Array arr2, int accumulate) {
  int start = 0;
  if (accumulate == 1) start = arr1->size;

  for (int i=0; i < arr2.size; ++i) {
    arr1->data[start] = arr2.data[i];
    ++start;
    arr1->size = start;
  }
};

void addArray(struct Array* arr1, int arr2[], int size, int accumulate) {
  int start = 0;
  if (accumulate == 1) start = arr1->size;

  for (int i=0; i < size; ++i) {
    arr1->data[start] = arr2[i];
    ++start;
    arr1->size = start;
  }
};

void swap(struct Array* arr, int i, int j) {
  int temp = arr->data[i];
  arr->data[i] = arr->data[j];
  arr->data[j] = temp;
};

void quick_sort(struct Array* arr, int start, int end){
  // pivot is always the first element. 
  // start end is used to partition the arry into 2 parts: left and right 
  // left is all the smaller element and right the greater ones.
  // if start >= end the recursion auto-stop
  if (start < end-1) {

    int pivot = arr->data[start];
    int rem = end; //better initialize with end.
    
    // Define the left and right by index start and end.
    for (int i=start+1; i < end; ++i) {
      if (arr->data[i] > pivot) {
        //remember the index of furthest leftside greater element
        if (rem > i) rem = i;
      }
      else {
        if (rem < i) {
          // only swap with the greater element at the leftside <=> rem < i
          swap(arr, i, rem);
          ++rem;
        }

        // swap with the closest leftside greater element, but not the pivot.
      }
      
    }

    // Insert the pivot to the closest leftside greater position.
    swap(arr, start, rem-1);

    // new recursion step
    quick_sort(arr, start, rem-1); //the left half.
    quick_sort(arr, rem, end); //the left half.
  }


};


struct Array to_array(char cStr[]) {
  struct Array arr;
  char temp[strlen(cStr)], check;

  int j=0, i=0, m=0;
  while (check = cStr[i]) {
    if (check == '-') {
      temp[j] = '\0'; // make an end for a string

      char* ptr;
      arr.data[m] = strtol(temp, &ptr, 10);
      ++m;
      arr.size = m;

      temp[0] = '\0'; // delete string temp
      j=0;  //reset j
    }
    else {
      temp[j] = check;
      ++j;
    }

    ++i;
  }

  return arr;

};


VALUE prepare(VALUE self, VALUE arrStr, VALUE size) {
  char* cStr = StringValuePtr(arrStr);  
  structSize = NUM2ULL(size);  //reset the size of the Struct Array

  struct Array arr = to_array(cStr);

  // appy quick sorting
  quick_sort(&arr, 0, arr.size);
  
  rb_gv_set("$q", LONG2FIX(arr.data[2]));

  // convert to ruby string
  VALUE rbArr = rb_ary_new();
  for (int i=0; i < arr.size; ++i) {
    rb_ary_push(rbArr, LONG2FIX(arr.data[i]));
  }
  
  return rbArr;
};


void Init_quickSort(void) {
  rb_define_singleton_method(mKhanh, "qSort", prepare, 2);

}

