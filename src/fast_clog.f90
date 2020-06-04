      subroutine fast_clog(re, im, out_re, out_im) bind(C, name="fast_clog_")
      implicit   none
      double precision, intent(in)  :: re,im
      double precision, intent(out) :: out_re,out_im

      out_re = 0.5d0*log(re*re + im*im)
      out_im = atan2(im, re)

      end subroutine
