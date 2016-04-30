# Checking the utilization of the compute resources 
class Performance
  def initialize(max)
    @max = max
  end
  def utilization
    yield(4,5) + yield(@max,@max)
  end
  def count cpu
    if cpu > @max
      raise "reached max"
    elsif yield cpu
      1
    else
      1+ (count(cpu+1) { |i| yield i })
    end
  end
end
