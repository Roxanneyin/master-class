function f_x = payoff(x,a,b)
if (x>0) & (x<=1)
    f_x = max(x-a,0);
elseif (x>1) & (x<=1.5)
    f_x = a;
elseif (x>1.5)
    f_x = max(b-x,0);
end
end

