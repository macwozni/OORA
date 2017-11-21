#define SIZE 512


program main
   integer(kind = 4) :: i, j, iret
   real (kind = 4) :: first(SIZE, SIZE)
   real (kind = 4) :: second(SIZE, SIZE)
   real (kind = 4) :: multiply(SIZE, SIZE)
   real (kind = 4) :: dtime

   do i = 1,SIZE
      do j = 1,SIZE
         first(i,j) = i + j;
         second(i,j) = i - j;
         multiply(i,j) = 0.d0;
      end do
   end do

end