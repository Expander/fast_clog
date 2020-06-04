      subroutine fast_clog(re, im, out_re, out_im) bind(C, name="fast_clog_")
      implicit   none
      real*8, intent(in)  :: re,im
      real*8, intent(out) :: out_re,out_im

      out_re = 0.5d0*log(re*re + im*im)
      out_im = datan2(im, re)

      end subroutine
