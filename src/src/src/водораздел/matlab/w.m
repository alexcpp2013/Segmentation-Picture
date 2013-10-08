 rgb=imread('D:\house0.jpg');
  I=rgb2gray(rgb);
  imshow(I);
text(732,501,'…',...
     'FontSize',7,'HorizontalAlignment','right');
 
 hy=fspecial('sobel');
hx=hy';
Iy=imfilter(double(I), hy, 'replicate');
Ix=imfilter(double(I), hx, 'replicate');
gradmag=sqrt(Ix.^2+Iy.^2);
figure, imshow(gradmag,[]), title('значение градиента')

L=watershed(gradmag);
Lrgb=label2rgb(L);
figure, imshow(Lrgb), title('Lrgb');

se=strel('disk', 20);
Io=imopen(I, se);
figure, imshow(Io), title('Io');

Ie=imerode(I, se);
Iobr=imreconstruct(Ie, I);
figure, imshow(Iobr), title('Iobr');

Ioc=imclose(Io, se);
figure, imshow(Ioc), title('Ioc');

Iobrd=imdilate(Iobr, se);
Iobrcbr=imreconstruct(imcomplement(Iobrd), imcomplement(Iobr));
Iobrcbr=imcomplement(Iobrcbr);
figure, imshow(Iobrcbr), title('Iobrcbr');

 fgm=imregionalmax(Iobrcbr);
 figure, imshow(fgm), title('fgm');

 I2=I;
 I2(fgm)=255;
 figure, imshow(I2), title('fgm, наложенное на исходное изображение')

 se2=strel(ones(5, 5));
 fgm2=imclose(fgm, se2);
 fgm3=imerode(fgm2, se2);
 
 fgm4=bwareaopen(fgm3, 20);
 I3=I;
 I3(fgm4)=255;
 figure, imshow(I3)
 title('fgm4, наложенное на исходное изображение');
 
   bw=im2bw(Iobrcbr, graythresh(Iobrcbr));
  figure, imshow(bw), title('bw')

  D=bwdist(bw);
  DL=watershed(D);
  bgm=DL==0;
  figure, imshow(bgm), title('bgm');
  
    gradmag2=imimposemin(gradmag, bgm | fgm4);
    
      L=watershed(gradmag2);
      
        I4=I;
  I4(imdilate(L==0, ones(3, 3))|bgm|fgm4)=255;
  figure, imshow(I4)
  title('Маркеры и границы объектов, наложенные на исходное изображение')

    Lrgb=label2rgb(L, 'jet', 'w', 'shuffle');
  figure, imshow(Lrgb)
  title('Lrgb')

    figure, imshow(I), hold on
  himage=imshow(Lrgb);
  set(himage, 'AlphaData', 0.3);
  title('Lrgb, наложенное на исходное изображение в полупрозрачном режиме')


