import java.io.*;
import java.util.*;


public class Main {
    public static void main(String[] args) throws Exception {
        FileReader fr = new FileReader("InputGS.txt");
        ExamRecords examRecord1 = new ExamRecords();
        examRecord1.readGroupSession(new BufferedReader(fr));

        ExamRecords examRecord2 = new ExamRecords();
        FileReader fr2 = new FileReader("InputGS2.txt");
        examRecord2.readGroupSession(new BufferedReader(fr2));

        ExamRecords examRecord3 = new ExamRecords();
        FileReader fr3 = new FileReader("InputGS3.txt");
        examRecord3.readGroupSession(new BufferedReader(fr3));




        ArrayList<ExamRecords> examRecords = new ArrayList<>();
        examRecords.add(examRecord1);
        examRecords.add(examRecord2);
        examRecords.add(examRecord3);

        //System.out.println(examRecords);

        Collections.sort(examRecords, new NameComparator());

        //System.out.println(examRecords);



        int index = Collections.binarySearch(examRecords, examRecord1, new NameComparator());
        if(index >= 0)
        {
            //System.out.println(examRecords.get(index).getStudName());
            //System.out.println(examRecords.get(index).getRecordNumber());
        }
        else
        {
            throw new Exception();
        }
        examRecords.clear();

        examRecords.add(examRecord1);
        examRecords.add(examRecord2);
        examRecords.add(examRecord3);

        Collections.sort(examRecords);
        index = Collections.binarySearch(examRecords, examRecord1);

        if(index >= 0)
        {
            //System.out.println(examRecords.get(index).getStudName());
            //System.out.println(examRecords.get(index).getRecordNumber());
        }
        else
        {
            throw new Exception();
        }


//        double average = ExamRecords.AverageMarkSubject(examRecords, 2, "Math");
//        System.out.println(average);
////
//        System.out.println(examRecord1);
//        System.out.println(examRecord2);
//        System.out.println(examRecord3);

        Map<Integer, ExamRecords> map = new TreeMap<>();
        map.put(examRecord1.getRecordNumber(), examRecord1);
        map.put(examRecord2.getRecordNumber(), examRecord2);
        map.put(examRecord3.getRecordNumber(), examRecord3);
        for(Map.Entry<Integer, ExamRecords> el: map.entrySet())
        {
            System.out.print(el.getValue().getStudName()+ " ");
            System.out.println(el.getValue().getRecordNumber());
        }
    }
    static class NameComparator implements Comparator<ExamRecords> {
        @Override
        public int compare(ExamRecords o1, ExamRecords o2) {
            return o1.getStudName().compareTo(o2.getStudName());
        }
    }
}
