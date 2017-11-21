#define SIZE 512


subroutine mm(first, second, multiply, ret)
   implicit none
   real (kind = 8) :: first(SIZE, SIZE)
   real (kind = 8) :: second(SIZE, SIZE)
   real (kind = 8) :: multiply(SIZE, SIZE)
   integer (kind = 4) :: ret
   integer(kind = 4) :: i, j, k;
   real (kind = 8) :: sum
   sum = 0
end subroutine

program main
   implicit none
   integer(kind = 4) :: i, j, iret
   real (kind = 8) :: first(SIZE, SIZE)
   real (kind = 8) :: second(SIZE, SIZE)
   real (kind = 8) :: multiply(SIZE, SIZE)
   real (kind = 8) :: dtime

   do i = 1, SIZE
      do j = 1, SIZE
         first(i, j) = i + j;
         second(i, j) = i - j;
         multiply(i, j) = 0.d0;
      end do
   end do

end