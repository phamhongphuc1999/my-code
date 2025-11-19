import { Entity, PrimaryGeneratedColumn, Column } from 'typeorm';

@Entity('Productions')
export class Production {
  @PrimaryGeneratedColumn()
  id: number;

  @Column()
  Name: string;

  @Column()
  Amount: number;

  @Column()
  UserId: number;
}
