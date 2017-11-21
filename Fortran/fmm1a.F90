#define SIZE 512


subroutine mm(first, second, multiply, ret)
   implicit none
   real (kind = 8), intent(in) :: first(SIZE, SIZE)
   real (kind = 8), intent(in) :: second(SIZE, SIZE)
   real (kind = 8), intent(out) :: multiply(SIZE, SIZE)
   integer (kind = 4), intent(out) :: ret
   integer(kind = 4) :: i, j, k
   real (kind = 8) :: sum

   sum = 0.d0
   multiply = 0.d0

   do j = 1, SIZE ! rows in multiply
      do k = 1, SIZE 
         do i = 1, SIZE ! columns in mmultiply
            multiply(i, j) = multiply(i, j) + first(i, k) * second(k, j)
         end do
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
   integer (kind = 4) :: iclock

   do i = 1, SIZE
      do j = 1, SIZE
         first(i, j) = i + j
         second(i, j) = i - j
      end do
   end do
   !multiply = 0.d0 ! this is much faster than putting that in loop !!

   call start_clock(iclock)

   ! Here is call to matrix multiplication functionality
   call mm(first, second, multiply, iret)

   call stop_clock(dtime, iclock)
   write(*, *) 'dtime : ', dtime

   ! Checking part of the code. Proper value is 2.932020e+12
   mcheck = 0.d0
   do i = 1, SIZE
      do j = 1, SIZE
         mcheck = mcheck + multiply(i, j)
      end do
   end do

   write (*, *) "check", mcheck
end