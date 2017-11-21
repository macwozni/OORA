#define SIZE 512


subroutine mm(first, second, multiply, ret)
   implicit none
   real (kind = 8), intent(in) :: first(SIZE, SIZE)
   real (kind = 8), intent(in) :: second(SIZE, SIZE)
   real (kind = 8), intent(out) :: multiply(SIZE, SIZE)
   integer (kind = 4), intent(out) :: ret
   integer(kind = 4) :: i, j, k, jj, kk
   real (kind = 8) :: sum
   integer (kind = 4) :: ichunk

   ! use -funroll-loops
   ichunk = 512 ! I have a 3MB cache size (real*4)
   do jj = 1, SIZE, ichunk
      do kk = 1, SIZE, ichunk

         do j = jj, min(jj + ichunk - 1, SIZE)
            do k = kk, min(kk + ichunk - 1, SIZE)
               do i = 1, SIZE
                  multiply(i, j) = multiply(i, j) + first(i, k) * second(k, j)
               end do
            end do
         end do

      end do
   end do


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