subroutine start_clock(Icount)
   integer(kind = 4), intent(inout) :: Icount
   integer(kind = 4) :: ir, im

   call system_clock(Icount, ir, im)

end subroutine start_clock


subroutine stop_clock(Dtime, Icount)
   integer(kind = 4), intent(in) :: Icount
   real(kind = 8), intent(out) :: Dtime
   integer(kind = 4) :: ic, ir, im

   call system_clock(ic, ir, im)
   write(*, *) 'start time ', Icount, ' stop time', ic

   if (ic > Icount) then
      Dtime = dble(ic - Icount)/dble(ir)
   elseif (ic < Icount) then
      Dtime = dble(im + ic - Icount)/dble(ir)
   else
      Dtime = 0.d0
   endif

end subroutine stop_clock

subroutine reset_clock(Dtime, Icount)
   integer Icount
   double precision Dtime

   call stop_clock(Dtime, Icount)
   call start_clock(Icount)

end subroutine reset_clock
