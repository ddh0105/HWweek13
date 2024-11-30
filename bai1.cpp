#include<bits/stdc++.h>
using namespace std;

#define max 1000
#define ll long long

//Struct luu thong tin san pham
struct Product{
    string tensanpham;
    int soluong;
    ll gia;
};

//Node de luu tru thong tin khach hang dang cho thanh toan
struct KH{
    string idKhachhang;
    Product* products;
    int tongsoluong;
    ll tongtien;
    KH* next;
};

//Queue
struct Queue{
    KH *front;//diem dau hang doi
    KH *rear;//diem cuoi hang doi
    ll doanhthu;

    struct Sales{
        string tensp;
        int soluong;
        Sales* next;
    } *productSales;

};

//Khoi tao hang doi
void initQueue(Queue &q){
    q.front = q.rear = NULL;
    q.doanhthu = 0;
    q.productSales = NULL;
}

//Kiem tra hang doi rong
bool isEmpty(Queue &q){
    return (q.front == NULL);
}

bool isFull(){
    return false;//do da cap phat dong nen hang doi se khong day
}

//Them khach hang vao hang doi
void enQueue(Queue &q, const string& IDCus, Product *products, int soluongSP){
    //Tao mot not moi
    KH *newKH = new KH;
    newKH->idKhachhang = IDCus;
    newKH->products =new Product[soluongSP];
    for (int i = 0; i < soluongSP; ++i){
        newKH->products[i] = products[i];
    }
    newKH->tongsoluong = soluongSP;
    newKH->tongtien = 0;
    for(int i = 0; i < soluongSP; ++i){
        newKH->tongtien+=products[i].gia*products[i].soluong;
    }
    newKH->next = NULL;

    //them NodeKH vao hang doi
    if (isEmpty(q)){
        q.front = q.rear = newKH;
    }
    else {
        q.rear ->next = newKH;
        q.rear = newKH;
    }
}

//Cap nhat so luong san pham da ban
void productSales(Queue &q, const string& tensp, int soluong){
    Queue::Sales *cur = q.productSales;
    while(cur != NULL){
        if (cur->tensp == tensp ){
            cur->soluong += soluong;
            return;
        }
        cur = cur->next;
    }
    //Cap nhat san pham moi neu san pham chua ton tai
    Queue::Sales *newSale = new Queue::Sales;
    newSale->tensp = tensp;
    newSale->soluong = soluong;
    newSale->next = q.productSales;
    q.productSales = newSale;
}


//Thanh toan cho khach hang dau
void deQueue(Queue &q){
    if (isEmpty(q)){
        cout<< "Khong co khach hang nao doi thanh toan!"<< endl;
        return; 
    }

    KH *trunggian = q.front;
    q.front = q.front->next;

    //Hang doi trong sau khi xoa
    if (isEmpty(q)){
        q.rear = NULL;
    }

    //Update doanh thu
    q.doanhthu += trunggian->tongtien;

    //Cap nhat so luong san pham da ban
    for (int i = 0; i < trunggian->tongsoluong; ++i){
        productSales(q, trunggian->products[i].tensanpham, trunggian->products[i].soluong);

    }


    //Giai phong bo nho
    delete[] trunggian->products;
    delete trunggian;
}

//Tinh tong doanh thu
ll tongDoanhthu(Queue &q){
    return q.doanhthu;
}

//Lay so luong san pham A da ban
int getProductAsale(Queue &q, const string &tensp){
    Queue::Sales *cur = q.productSales;
    while (cur != NULL){
        if (cur->tensp == tensp){
            return cur->soluong;
        }
        cur = cur->next;
    }
    return 0;
}

//Giai phong hang doi
void deleteQueue(Queue &q){
    while (!isEmpty(q)){
        deQueue(q);
    }
    while (q.productSales != NULL){
        Queue::Sales *trunggian = q.productSales;
        q.productSales = q.productSales->next;
        delete trunggian;
    }
}

int main(){
    Queue q;
    initQueue(q);
    //KH1
    Product pro1[] = {
        {"B", 2, 50000},
        {"A", 5, 200000}

    };
    enQueue(q, "KH001", pro1, 2);

    //KH2
    Product pro2[] = {
        {"C", 3, 25000}, {"A", 3, 200000}
    };
    enQueue(q, "KH002", pro2, 2 );

    //KH3
    Product pro3[] ={
        {"A", 1, 200000},
        {"B", 2, 50000},
        {"C", 1, 25000}
    };
    enQueue(q, "KH003", pro3, 3);

    //Thanh toan
    deQueue(q);//ttKH001
    deQueue(q);//ttKH002
    deQueue(q);//ttKH003

    //Tong doanh thu
    cout << "Tong tien thu ngan lam viec trong ca lam viec: "<<tongDoanhthu(q)<<" VND"<<endl;

    //So luong san pham A ban ra
    cout <<"So luong san pham A ban ra la: "<<getProductAsale(q, "A")<<endl;

    //Giai phong bo nho
    deleteQueue(q);

    return 0;
}