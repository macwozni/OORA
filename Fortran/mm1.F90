#define SIZE 512


subroutine mm(first, second, multiply, ret)
   implicit none
   real (kind = 8), intent(in) :: first(SIZE, SIZE)
   real (kind = 8), intent(in) :: second(SIZE, SIZE)
   real (kind = 8) :: multiply(SIZE, SIZE)
   integer (kind = 4), intent(out) :: ret
   integer(kind = 4) :: i, j, k;
   real (kind = 8) :: sum
   sum = 0.d0

   do i = 1, SIZE !rows in multiply
      do j = 1, SIZE !columns in mmultiply
         do k = 1, SIZE
            sum = sum + first(i, k) * second(k, j)
         end do
         multiply(i, j) = sum
         sum = 0.d0
      end do
   end do
   ret = 0.d0

end subroutine

program main
   implicit none
   integer(kind = 4) :: i, j, iret
   real (kind = 8) :: first(SIZE, SIZE)
   real (kind = 8) :: second(SIZE, SIZE)
   real (kind = 8) :: multiply(SIZE, SIZE)
   real (kind = 8) :: dtime
   real (kind = 8) :: mcheck

   do i = 1, SIZE
      do j = 1, SIZE
         first(i, j) = i + j
         second(i, j) = i - j
      end do
   end do
   multiply = 0.d0 ! this is much faster than putting that in loop !!

   call mm(first, second, multiply, iret)

   mcheck = 0.d0;
   do i = 1, SIZE
      do j = 1, SIZE
         mcheck = mcheck + multiply(i, j)
      end do
   end do

   write (*, *) "check", mcheck;
end