#include <khanh.h>


struct Array {
  int size;
  long* data;
};

void print(struct Array arr) {
  for (int i=0; i < arr.size; ++i) printf("%li ", arr.data[i]);
  printf("(%d) \n", arr.size);
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


void to_array(long* container, char cStr[], int size) {
  
  char temp[size], check;
  
  int j=0, i=0, m=0;
  while (check = cStr[i]) {
    if (check == '-') {
      temp[j] = '\0'; // make an end for a string

      char* ptr;
      container[m] = strtol(temp, &ptr, 10);

      ++m;
      temp[0] = '\0'; // delete string temp
      j=0;  //reset j
    }
    else {
      temp[j] = check;
      ++j;
    }

    ++i;
  }

  
  

};


VALUE prepare(VALUE self, VALUE arrStr, VALUE size) {
  char* cStr = StringValuePtr(arrStr);
  int arrSize = NUM2ULL(size);

  struct Array arr;
  long* container;
  container = (long*) malloc(arrSize * sizeof(long));
  to_array(container, cStr, arrSize);

  arr.data = &container[0];
  arr.size = arrSize;
  

  // appy quick sorting
  quick_sort(&arr, 0, arr.size);
  
  rb_gv_set("$q", LONG2FIX(arr.data[2]));

  // convert to ruby string
  VALUE rbArr = rb_ary_new();
  for (int i=0; i < arr.size; ++i) {
    rb_ary_push(rbArr, LONG2FIX(arr.data[i]));
  }

  // free malloc
  free(container);
  
  return rbArr;
};


void Init_quickSort(void) {
  rb_define_singleton_method(mKhanh, "qSort", prepare, 2);

}

