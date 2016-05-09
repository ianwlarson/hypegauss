# This is a script file;
1;

function ret = norm (x)
    ret = 1 / sqrt(2*pi) * exp(-1 * x.^2 / 2);
endfunction

function ret = inv_norm (x)
    ret = sqrt(-2 * log(sqrt(2*pi) * x));
endfunction

function ret = v(r, f)
    q = zeros([size(r)(1) 1]);
    for i = size(r)(1):1
        [q(i), ier] = quadgk(f, r(i), Inf);
    endfor

    ret = r .* f(r) .+ q;
endfunction

function ret = z (r)
    x = zeros([size(r)(1) 256]);
    x(:, 256) = r;
    
    l_v = v(r, @norm);
    
    for i = 255:-1:1     
        x(:, i) = inv_norm(l_v ./ x(:, i+1) .+ norm(x(:, i+1)));
    endfor

    ret = l_v .- x(:,1) .+ x(:,1) .* norm(x(:,1));
endfunction

g_r = fminsearch(@(y) abs(z(y)), 3.5)

x = zeros([1 256]);
x(256) = g_r;

g_v = v(g_r, @norm);

for i = 255:-1:1     
    x(:, i) = inv_norm(g_v ./ x(:, i+1) .+ norm(x(:, i+1)));
endfor

printf("\n")
for i = 1:256
    printf("%.9f, ", x(i))
endfor
printf("\n")
k = zeros([1 256]);
k(1) = floor(2**32 * g_r * norm(g_r) / g_v);
printf("k:\n")
for i = 2:256
    k(i) = floor(2**32 * x(i-1)/x(i));
endfor
for i = 1:256
    printf("%i, ", k(i))
endfor
printf("\n")
w = zeros([1 256]);
w(1) = 0.5**32 * g_v/norm(g_r);
printf("w:\n")
for i = 2:256
    w(i) = 0.5**32 * x(i);
endfor
for i = 1:256
    printf("%.16f, ", w(i))
endfor
printf("\n")

printf("f:\n")
for i = 1:256
    printf("%.12f, ", norm(x(i)))
endfor
printf("\n")